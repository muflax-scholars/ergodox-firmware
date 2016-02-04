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

// layer data
struct layer {
  bool   	active;
  uint8_t	sticky;
};

struct layer	layers[KB_LAYERS];
uint8_t     	layers_top = 0;


// ----------------------------------------------------------------------------

/*
 * main()
 */
int main(void) {
  kb_init(); // does controller initialization too

  usb_init();
  while (!usb_configured());

  // initialize layers
  for (uint8_t layer=0; layer < KB_LAYERS; layer++) {
    layers[layer].active = false;
    layers[layer].sticky = eStickyNone;
  }
  layers[0].active = true;

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
  }

  return 0;
}


// ----------------------------------------------------------------------------
// layer functions
// ----------------------------------------------------------------------------


// find highest active layer
uint8_t _highest_active_layer(uint8_t offset) {
  if (offset < layers_top) {
    for (uint8_t l = layers_top - offset; l > 0 && l < KB_LAYERS; l--) {
      if (layers[l].active) { return l; }
    }
  }

  // the base layer is always active
  return 0;
}

// return the highest active layer
uint8_t main_layers_top_layer() {
  return layers_top;
}

// return if highest active layer is sticky
uint8_t main_layers_top_sticky() {
  return layers[layers_top].sticky;
}

// enable a layer
void main_layers_enable(uint8_t layer, uint8_t sticky) {
  if (layer >= KB_LAYERS) { return; }

  layers[layer].active = true;
  layers[layer].sticky = sticky;

  if (layer > layers_top) {
    layers_top = layer;
  }
}

// disable a layer
void main_layers_disable(uint8_t layer) {
  if (layer >= KB_LAYERS) { return; }

  layers[layer].active = false;
  if (layer >= layers_top) {
    layers_top = _highest_active_layer(1);
  }
}

// disable the highest active layer
void main_layers_disable_top() {
  main_layers_disable(layers_top);
}

// return layer offset elements below the top
uint8_t main_layers_peek(uint8_t offset) {
  return _highest_active_layer(offset);
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
