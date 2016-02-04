/* ----------------------------------------------------------------------------
 * key functions : special : code
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdbool.h>
#include <stdint.h>
#include "../../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../../lib/usb/usage-page/keyboard.h"
#include "../../../keyboard/layout.h"
#include "../../../main.h"
#include "../public.h"
#include "../private.h"

// ----------------------------------------------------------------------------

/*
 * Generate a 'shift' press or release before the normal keypress or release
 */
void kbfun_shift_press_release(void) {
  _kbfun_press_release(main_arg_is_pressed, KEY_LeftShift);
  kbfun_press_release();
}

/*
 * Generate a 'control' press or release before the normal keypress or release
 */
void kbfun_control_press_release(void) {
  _kbfun_press_release(main_arg_is_pressed, KEY_LeftControl);
  kbfun_press_release();
}

/*
 * When assigned to two keys (e.g. the physical left and right shift keys)
 * (in both the press and release matrices), pressing and holding down one of
 * the keys will make the second key toggle capslock
 *
 * If either of the shifts are pressed when the second key is pressed, they
 * wil be released so that capslock will register properly when pressed.
 * Capslock will then be pressed and released, and the original state of the
 * shifts will be restored
 */
void kbfun_2_keys_capslock_press_release(void) {
  static uint8_t keys_pressed;
  static bool lshift_pressed;
  static bool rshift_pressed;

  uint8_t keycode = _kbfun_get_keycode();

  if (!main_arg_is_pressed) { keys_pressed--; }

// take care of the key that was actually pressed
  _kbfun_press_release(main_arg_is_pressed, keycode);

// take care of capslock (only on the press of the 2nd key)
  if (keys_pressed == 1 && main_arg_is_pressed) {
// save the state of left and right shift
    lshift_pressed = _kbfun_is_pressed(KEY_LeftShift);
    rshift_pressed = _kbfun_is_pressed(KEY_RightShift);
// disable both
    _kbfun_press_release(false, KEY_LeftShift);
    _kbfun_press_release(false, KEY_RightShift);

// press capslock, then release it
    _kbfun_press_release(true, KEY_CapsLock); 	usb_keyboard_send();
    _kbfun_press_release(false, KEY_CapsLock);	usb_keyboard_send();

// restore the state of left and right shift
    if (lshift_pressed)	{ _kbfun_press_release(true, KEY_LeftShift); 	}
    if (rshift_pressed)	{ _kbfun_press_release(true, KEY_RightShift);	}
  }

  if (main_arg_is_pressed) { keys_pressed++; }
}

/*
 * Generate a keypress for a media key
 */
void kbfun_mediakey_press_release(void) {
  uint8_t keycode = _kbfun_get_keycode();
  _kbfun_mediakey_press_release(main_arg_is_pressed, keycode);
}

/* ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */
