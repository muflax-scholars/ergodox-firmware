/* ----------------------------------------------------------------------------
 * main()
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "./lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "./lib/key-functions/public.h"
#include "./keyboard/controller.h"
#include "./keyboard/layout.h"
#include "./keyboard/matrix.h"
#include "./main.h"

// ----------------------------------------------------------------------------

// TODO remove this; for now we'll just limit it to the number of layers
#define MAX_ACTIVE_LAYERS KB_LAYERS

// ----------------------------------------------------------------------------

static bool _main_kb_is_pressed[KB_ROWS][KB_COLUMNS];
bool (*main_kb_is_pressed)[KB_ROWS][KB_COLUMNS] = &_main_kb_is_pressed;

static bool _main_kb_was_pressed[KB_ROWS][KB_COLUMNS];
bool (*main_kb_was_pressed)[KB_ROWS][KB_COLUMNS] = &_main_kb_was_pressed;

static bool main_kb_was_transparent[KB_ROWS][KB_COLUMNS];

uint8_t main_layers_pressed[KB_ROWS][KB_COLUMNS];

uint8_t main_arg_layer;
uint8_t main_arg_layer_offset;
uint8_t main_arg_row;
uint8_t main_arg_col;
bool    main_arg_is_pressed;
bool    main_arg_was_pressed;
bool    main_arg_any_non_trans_key_pressed;
bool    main_arg_trans_key_pressed;

// ----------------------------------------------------------------------------

/*
 * main()
 */
int main(void) {
  kb_init(); // does controller initialization too

  kb_led_state_power_on();

  usb_init();
  while (!usb_configured());
  kb_led_delay_usb_init();  // give the OS time to load drivers, etc.

  kb_led_state_ready();

  for (;;) {
    // swap `main_kb_is_pressed` and `main_kb_was_pressed`, then update
    bool (*temp)[KB_ROWS][KB_COLUMNS]	= main_kb_was_pressed;
    main_kb_was_pressed              	= main_kb_is_pressed;
    main_kb_is_pressed               	= temp;

    kb_update_matrix(*main_kb_is_pressed);

    // this loop is responsible to
    // - "execute" keys when they change state
    // - keep track of which layers the keys were on when they were pressed
    //   (so they can be released using the function from that layer)
    //
    // note
    // - everything else is the key function's responsibility
    //   - see the keyboard layout file ("keyboard/ergodox/layout/*.c") for
    //     which key is assigned which function (per layer)
    //   - see "lib/key-functions/public/*.c" for the function definitions
    for (uint8_t row=0; row<KB_ROWS; row++) {
      for (uint8_t col=0; col<KB_COLUMNS; col++) {
        main_arg_is_pressed 	= (*main_kb_is_pressed)[row][col];
        main_arg_was_pressed	= (*main_kb_was_pressed)[row][col];

        if (main_arg_is_pressed != main_arg_was_pressed) {
          if (main_arg_is_pressed) {
            main_arg_layer               	= main_layers_top_layer();
            main_layers_pressed[row][col]	= main_arg_layer;
            main_arg_trans_key_pressed   	= false;
          } else {
            main_arg_layer            	= main_layers_pressed[row][col];
            main_arg_trans_key_pressed	= main_kb_was_transparent[row][col];
          }

          // set remaining vars, and "execute" key
          main_arg_row         	= row;
          main_arg_col         	= col;
          main_arg_layer_offset	= 0;
          main_exec_key();
          main_kb_was_transparent[row][col] = main_arg_trans_key_pressed;
        }
      }
    }

    // send the USB report (even if nothing's changed)
    usb_keyboard_send();
    usb_extra_consumer_send();
    _delay_ms(MAKEFILE_DEBOUNCE_TIME);

    // update LEDs
    if (keyboard_leds & (1<<0))	{ kb_led_num_on();    	} else { kb_led_num_off();    	}
    if (keyboard_leds & (1<<1))	{ kb_led_caps_on();   	} else { kb_led_caps_off();   	}
    if (keyboard_leds & (1<<2))	{ kb_led_scroll_on(); 	} else { kb_led_scroll_off(); 	}
    if (keyboard_leds & (1<<3))	{ kb_led_compose_on();	} else { kb_led_compose_off();	}
    if (keyboard_leds & (1<<4))	{ kb_led_kana_on();   	} else { kb_led_kana_off();   	}
  }

  return 0;
}

// ----------------------------------------------------------------------------

/* ----------------------------------------------------------------------------
 * Layer Functions
 * ----------------------------------------------------------------------------
 * We keep track of which layer is foremost by placing it on a stack.  Layers
 * may appear in the stack more than once.  The base layer will always be
 * layer-0.
 *
 * Implemented as a fixed size stack.
 * ------------------------------------------------------------------------- */

// new array version

struct layer {
  bool   	active;
  uint8_t	sticky;
};

struct layer	layers[KB_LAYERS];
uint8_t     	layers_top = 0;

// old stack version

struct layer_stack {
  uint8_t	layer;
  uint8_t	id;
  uint8_t	sticky;
};

struct layer_stack	layers_stack[MAX_ACTIVE_LAYERS];
uint8_t           	layers_head = 0;
uint8_t           	layers_ids_in_use[MAX_ACTIVE_LAYERS] = {true};
uint8_t           	layer_ids[1 + KB_LAYERS];

// ----------------------------------------------------------------------------

// return the highest active layer
uint8_t main_layers_top_layer() {
  return layers_stack[layers_head].layer;

  // return layers_top;
}

// return if highest active layer is sticky
uint8_t main_layers_top_sticky() {
  return layers_stack[layers_head].sticky;

  // return layers[layers_top].sticky;
}

// disable the highest active layer
void main_layers_disable_top() {
  // TODO remove
  main_layers_pop_id(layers_head);

  main_layers_disable(layers_top);
}

// enable a layer
void main_layers_enable(uint8_t layer, uint8_t sticky) {
  // TODO remove
  layer_ids[layer] = main_layers_push(layer, sticky);

  // TODO
  if (layer > layers_top) {
    layers_top = layer;
  }
}

// disable a layer
void main_layers_disable(uint8_t layer) {
  // TODO remove
  main_layers_pop_id(layer_ids[layer]);
  layer_ids[layer] = 0;

  // TODO
  if (layer == layers_top) {
    // FIXME
  }
}

// execute the keypress or keyrelease function (if it exists) of the key at the current possition
void main_exec_key(void) {
  void (*key_function)(void) =
    ( (main_arg_is_pressed)
      ? kb_layout_press_get(main_arg_layer, main_arg_row, main_arg_col)
      : kb_layout_release_get(main_arg_layer, main_arg_row, main_arg_col) );

  if (key_function) {
    (*key_function)();
  }

  // If the current layer is in the sticky once up state and a key defined
  //  for this layer (a non-transparent key) was pressed, pop the layer
  if (main_layers_top_sticky() == eStickyOnceUp && main_arg_any_non_trans_key_pressed) {
    main_layers_disable_top();
  }
}









// TODO remove all this

/*
 * peek()
 *
 * Arguments
 * - 'offset': the offset (down the stack) from the head element
 *
 * Returns
 * - success: the layer-number of the requested element (which may be 0)
 * - failure: 0 (default) (out of bounds)
 */
uint8_t main_layers_peek(uint8_t offset) {
  if (offset <= layers_head) {
    return layers_stack[layers_head - offset].layer;
  }

  return 0; // default, or error
}

/*
 * push()
 *
 * Arguments
 * - 'layer': the layer-number to push to the top of the stack
 *
 * Returns
 * - success: the id assigned to the newly added element
 * - failure: 0 (the stack was already full)
 */
uint8_t main_layers_push(uint8_t layer, uint8_t sticky) {
  // look for an available id
  for (uint8_t id=1; id<MAX_ACTIVE_LAYERS; id++) {
    // if one is found
    if (layers_ids_in_use[id] == false) {
      layers_ids_in_use[id]           	= true;
      layers_head++;                  	
      layers_stack[layers_head].layer 	= layer;
      layers_stack[layers_head].id    	= id;
      layers_stack[layers_head].sticky	= sticky;
      return id;
    }
  }

  return 0; // default, or error
}

/*
 * pop_id()
 *
 * Arguments
 * - 'id': the id of the element to pop from the stack
 */
void main_layers_pop_id(uint8_t id) {
  // look for the element with the id we want to pop
  for (uint8_t element=1; element<=layers_head; element++) {
    // if we find it
    if (layers_stack[element].id == id) {
      // move all layers above it down one
      for (; element<layers_head; element++) {
        layers_stack[element].layer	= layers_stack[element+1].layer;
        layers_stack[element].id   	= layers_stack[element+1].id;
      }
      // reinitialize the topmost (now unused) slot
      layers_stack[layers_head].layer	= 0;
      layers_stack[layers_head].id   	= 0;
      // record keeping
      layers_ids_in_use[id] = false;
      layers_head--;
    }
  }
}
