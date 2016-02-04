/* ----------------------------------------------------------------------------
 * key functions : public exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef LIB__KEY_FUNCTIONS__COMMON_h
#define LIB__KEY_FUNCTIONS__COMMON_h

#include <stdbool.h>
#include <stdint.h>

// --------------------------------------------------------------------

// basic
void kbfun_press_release                	(void);
void kbfun_press_release_preserve_sticky	(void);
void kbfun_toggle                       	(void);
void kbfun_transparent                  	(void);

// layer push/pop functions
#define simple_layer(n) \
  void kbfun_layer_push_##n  	(void); \
  void kbfun_layer_sticky_##n	(void); \
  void kbfun_layer_pop_##n   	(void);

simple_layer(1);
simple_layer(2);
simple_layer(3);
simple_layer(4);
simple_layer(5);
simple_layer(6);
simple_layer(7);
simple_layer(8);
simple_layer(9);
simple_layer(10);

// device
void kbfun_jump_to_bootloader (void);

// special
void kbfun_shift_press_release          	(void);
void kbfun_control_press_release        	(void);
void kbfun_2_keys_capslock_press_release	(void);
void kbfun_mediakey_press_release       	(void);

#endif
