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

// helper functions

static bool is_layer_enable(void_funptr_t f) {
  if (f == &kbfun_layer_enable || f == &kbfun_layer_sticky) {
    return true;
  }
  return false;
}

static bool is_layer_disable(void_funptr_t f) {
  if (f == &kbfun_layer_disable || f == &kbfun_layer_sticky) {
    return true;
  }
  return false;
}

static void layer_enable_upto(uint8_t max_layer) {
  // FIXME clean this up

  // pressing a key implicitly activates all lower layers as well
  for (uint8_t layer=0; layer <= KB_LAYERS; layer++) {
    void (*key_function)(void) = kb_layout_press_get(layer, main_arg_row, main_arg_col);

    if (is_layer_enable(key_function)) {
      uint8_t enable_layer = kb_layout_get(layer, main_arg_row, main_arg_col);
      if (enable_layer <= max_layer) {
        main_layers_enable(enable_layer, eStickyNone);
      }
    }
  }
}

static void layer_disable_all() {
  // FIXME clean this up

  // letting go off a key releases *all* layers on that key
  for (uint8_t layer=0; layer <= KB_LAYERS; layer++) {
    void (*key_function)(void) = kb_layout_release_get(layer, main_arg_row, main_arg_col);

    if (is_layer_disable(key_function)) {
      uint8_t disable_layer = kb_layout_get(layer, main_arg_row, main_arg_col);
      main_layers_disable(disable_layer);
    }
  }
}

// actual functions

// enable given layer
void kbfun_layer_enable() {
  uint8_t layer = _kbfun_get_keycode();

  // FIXME useful for anything?
  // Only the topmost layer on the stack should be in sticky once state, pop
  // the top layer if it is in sticky once state
  /* uint8_t topSticky = main_layers_top_sticky(); */
  /* if (topSticky == eStickyOnceDown || topSticky == eStickyOnceUp) { */
  /*   main_layers_disable_top(); */
  /* } */

  layer_enable_upto(layer);
}

// disable given layer
void kbfun_layer_disable() {
  /* uint8_t layer = _kbfun_get_keycode(); */
  layer_disable_all();
}

/*
 * This function gives similar behavior to sticky keys for modifiers available
 *  on most operating systems.
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
void kbfun_layer_sticky() {
  uint8_t layer    	= _kbfun_get_keycode();
  uint8_t topLayer 	= main_layers_top_layer();
  uint8_t topSticky	= main_layers_top_sticky();

  if (main_arg_is_pressed) {
    if (topLayer == layer) {
      // FIXME
      /* if (topSticky == eStickyOnceUp) { */
      /*   main_layers_enable(layer, eStickyLock); */
      /* } */
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
    if (main_layers_sticky(layer) == eStickyOnceDown) {
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
