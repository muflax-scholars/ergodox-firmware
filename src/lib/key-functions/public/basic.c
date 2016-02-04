/* ----------------------------------------------------------------------------
 * key functions : basic : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include "../../../main.h"
#include "../../../keyboard/layout.h"
#include "../public.h"
#include "../private.h"

/*
 * Generate a normal keypress or keyrelease
 */
void kbfun_press_release() {
  if (!main_arg_trans_key_pressed) {
    main_arg_any_non_trans_key_pressed = true;
  }
  kbfun_press_release_preserve_sticky();
}

/*
 * Generate a normal keypress or keyrelease
 * While basing the sticky key state transition on whether
 *  kbfun_press_release() was called after kbfun_transparent() generally
 *  works in practice, it is not always the desired behavior. One of the
 *  benefits of sticky keys is avoiding key chording, so we want to make sure
 *  that standard modifiers do not interrupt the sticky key cycle. Use
 *  kbfun_press_release_preserve_sticky() if you want to define a standard
 *  modifier key (shift, control, alt, gui) on the sticky layer instead of
 *  defining the key to be transparent for the layer.
 */
void kbfun_press_release_preserve_sticky() {
  uint8_t keycode = _kbfun_get_keycode();
  _kbfun_press_release(main_arg_is_pressed, keycode);
}

/*
 * Toggle the key pressed or unpressed
 */
void kbfun_toggle(void) {
  uint8_t keycode	= _kbfun_get_keycode();
  bool is_pressed	= _kbfun_is_pressed(keycode);
  _kbfun_press_release(!is_pressed, keycode);
}

/*
 * Execute the key that would have been executed if the current layer was not
 * active
 */
void kbfun_transparent(void) {
  // TODO maybe re-implement this cleaner?
  main_arg_trans_key_pressed = true;
  main_arg_layer_offset++;
  main_arg_layer = main_layers_peek(main_arg_layer_offset);
  main_layers_pressed[main_arg_row][main_arg_col] = main_arg_layer;
  main_exec_key();
}


/* ----------------------------------------------------------------------------
 * layer functions
 * ------------------------------------------------------------------------- */

// enable given layer
static void layer_enable(uint8_t layer) {
  // Only the topmost layer on the stack should be in sticky once state, pop
  // the top layer if it is in sticky once state
  uint8_t topSticky = main_layers_top_sticky();
  if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) {
    main_layers_disable_top();
  }

  main_layers_enable(layer, eStickyNone);
}

// disable given layer
static void layer_disable(uint8_t layer) {
  main_layers_disable(layer);
}

/*
 * This function gives similar behavior to sticky keys for modifiers available
 *  on most operating systems. It is considered an accessibility feature
 *  because it alleviates the user from having to hold down modifiers while
 *  pressing a key to produce the modified key function. It is useful for fast
 *  touch typing because you can avoid chording motions which both strain your
 *  hands and take your hands out of home-row position while pressing normal
 *  alpha keys.
 * This function emulates the 3-state behavior which is default on OS X and
 *  optional in Windows where the modifier cycles between Off->Once->Locked
 *  states. This is particularly handy for symbol layers where you typically
 *  only type one symbol before you want to return to unmodified typing (layer
 *  0), e.g. 'if (condition) { a = "b" + "c"; }'. If you assign a symbol layer
 *  to a thumb key as a layer sticky cycle, you can type the entire line of
 *  code without taking your hands out of home row position and you do not need
 *  to toggle off the layer after each symbol is pressed, only immediately
 *  before keying the symbol.
 * The exact behavior of the layer sticky cycle function is defined as follows
 *  for each state:
 * 1) One time down (set on key press) - The layer was not active and the key
 *     has been pressed but not yet released. The layer is pushed in the one
 *     time down state.
 * 2) One time up (set on key release) - The layer was active when the layer
 *     sticky key was released. If a key on this layer (not set to
 *     transparent) was pressed before the key was released, the layer will be
 *     popped. If a non-transparent key was not pressed, the layer is popped
 *     and pushed again in the one time up state.
 * 3) Locked (set on key press) - The layer was active and in the one time up
 *     state when the layer sticky key was pressed again. The layer will be
 *     popped if the function is invoked on a subsequent keypress.
 */
static void layer_sticky(uint8_t layer) {
  uint8_t topLayer 	= main_layers_top_layer();
  uint8_t topSticky	= main_layers_top_sticky();

  if (main_arg_is_pressed) {
    if (topLayer == layer) {
      if (topSticky == eStickyOnceUp) {
        main_layers_enable(layer, eStickyLock);
      }
    } else {
      // only the topmost layer on the stack should be in sticky once state
      if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) {
        main_layers_disable_top();
      }
      main_layers_enable(layer, eStickyOnceDown);

      // this should be the only place we care about this flag being cleared
      main_arg_any_non_trans_key_pressed = false;
    }
  } else {
    if (topLayer == layer) {
      if (topSticky == eStickyOnceDown) {
        // When releasing this sticky key, pop the layer always
        main_layers_disable(layer);
        if (!main_arg_any_non_trans_key_pressed) {
          // If no key defined for this layer (a non-transparent key)
          //  was pressed, push the layer again, but in the
          //  StickyOnceUp state
          main_layers_enable(layer, eStickyOnceUp);
        }
      }
    }
  }
}

// actual functions

void kbfun_layer_enable(void) {
  uint8_t keycode = _kbfun_get_keycode();
  layer_enable(keycode);
}

void kbfun_layer_sticky(void) {
  uint8_t keycode = _kbfun_get_keycode();
  layer_sticky(keycode);
}
void kbfun_layer_disable(void) {
  uint8_t keycode = _kbfun_get_keycode();
  layer_disable(keycode);
}
