/* ----------------------------------------------------------------------------
 * ergoDOX layout : saneo
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // layout: layer 0: default
// unused
0,
// left hand
_0,     	_1,     	_2,     	_3,     	_4,    	_5,         	_6,
0,      	_Q,     	_W,     	_E,     	_R,    	_T,         	0,
1,      	_A,     	_S,     	_D,     	_F,    	_G,
_shiftL,	_Z,     	_X  ,   	_C,     	_V,    	_B,         	0,
_arrowL,	_arrowU,	_arrowD,	_arrowR,	_guiL, 	
        	        	        	        	       	_scrollLock,	0,
        	        	        	        	0,     	0,          	0,
        	        	        	        	_space,	_ctrlL,     	_altL,
// right hand
_5,   	_6,	_7,       	_8,    	_9,     	_0,        	0,
0,    	_Y,	_U,       	_I,    	_O,     	_P,        	_bracketL,
      	_H,	_J,       	_K,    	_L,     	_semicolon,	1,
0,    	_N,	_M,       	_comma,	_period,	_slash,    	_shiftL,
      	   	2,        	0,     	0,      	0,         	0,
0,    	0, 	
0,    	0, 	0,
_menu,	2, 	_shiftR ),


	KB_MATRIX_LAYER(  // layout: layer 1: function and symbol keys
// unused
0,
// left hand
0,	_F1,   	_F2,      	_F3,       	_F4,   	_F5,       	_F11,
0,	_grave,	_bracketL,	_quote,    	_comma,	_backslash,	0,   	
0,	_comma,	_bracketL,	_slash,    	_1,    	_9,        	     	
0,	_grave,	_6,       	_backslash,	_dash, 	_2,        	0,   	
0,	0,     	0,        	0,         	0,     	           	
  	       	          	           	       	0,         	0,
  	       	          	           	0,     	0,         	0,
  	       	          	           	0,     	0,         	0,
// right hand
_F12,	_F6,   	_F7,    	_F8,   	_F9,      	_F10,   	0,
0,   	_equal,	_period,	_quote,	_bracketR,	_grave, 	0,	
     	_0,    	_dash,  	_slash,	_bracketR,	_period,	0,	
0,   	_equal,	_4,     	_7,    	_3,       	_6,     	0,	
     	       	0,      	0,     	0,        	0,      	0,	
0,   	0,     	
0,   	0,     	0,
0,   	0,     	0 ),


	KB_MATRIX_LAYER(  // layout: layer 2: keyboard functions
// unused
0,
// left hand
0,	0,      	0,      	0,      	0,      	0,      	0,	
0,	_esc,   	_bs,    	_enter, 	_del,   	_insert,	0,	
0,	_arrowL,	_arrowU,	_arrowD,	_arrowR,	_tab,   	  	
0,	_home,  	_pageU, 	_pageD, 	_end,   	0,      	0,	
0,	0,      	0,      	0,      	0,      	        	
  	        	        	        	        	0,      	0,
  	        	        	        	0,      	0,      	0,
  	        	        	        	0,      	0,      	0,
// right hand
0,	0,	0,  	0,	0,	0,	0,	
0,	0,	0,  	0,	0,	0,	0,	
  	0,	0,  	0,	0,	0,	0,	
0,	0,	0,  	0,	0,	0,	0,	
  	  	0,  	0,	0,	0,	0,	
0,	0,	
0,	0,	0,
0,	0,	0 ),

	KB_MATRIX_LAYER(  // layout: layer 3: numpad
// unused
0,
// left hand
0,	0,	0,	0,	0,	0,	0,	
0,	0,	0,	0,	0,	0,	0,	
0,	0,	0,	0,	0,	0,	  	
0,	0,	0,	0,	0,	0,	0,	
0,	0,	0,	0,	0,	  	
  	  	  	  	  	0,	0,
  	  	  	  	0,	0,	0,
  	  	  	  	0,	0,	0,
// right hand
0,	0,	0,  	0,	0,	0,	0,	
0,	0,	0,  	0,	0,	0,	0,	
  	0,	0,  	0,	0,	0,	0,	
0,	0,	0,  	0,	0,	0,	0,	
  	  	0,  	0,	0,	0,	0,	
0,	0,	
0,	0,	0,
0,	0,	0 ),

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// aliases

// basic
#define  kprrel  &kbfun_press_release
#define  ktog    &kbfun_toggle
#define  ktrans  &kbfun_transparent
// --- layer push/pop functions
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lpush3   &kbfun_layer_push_3
#define  lpush4   &kbfun_layer_push_4
#define  lpush5   &kbfun_layer_push_5
#define  lpush6   &kbfun_layer_push_6
#define  lpush7   &kbfun_layer_push_7
#define  lpush8   &kbfun_layer_push_8
#define  lpush9   &kbfun_layer_push_9
#define  lpush10  &kbfun_layer_push_10
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  lpop3    &kbfun_layer_pop_3
#define  lpop4    &kbfun_layer_pop_4
#define  lpop5    &kbfun_layer_pop_5
#define  lpop6    &kbfun_layer_pop_6
#define  lpop7    &kbfun_layer_pop_7
#define  lpop8    &kbfun_layer_pop_8
#define  lpop9    &kbfun_layer_pop_9
#define  lpop10   &kbfun_layer_pop_10
// ---

// device
#define  dbtldr  &kbfun_jump_to_bootloader

// special
#define  sshprre  &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // press: layer 0: default
// unused
NULL,
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 lpush1, kprrel, kprrel, kprrel, kprrel, kprrel,
 s2kcap, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel,
                                                 kprrel, kprrel,
                                           NULL,   NULL, kprrel,
                                         kprrel, kprrel, kprrel,
// right hand
         kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
         kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                 kprrel, kprrel, kprrel, kprrel, kprrel, lpush1,
         kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, s2kcap,
                         lpush2, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel,   NULL,   NULL,
 kprrel, lpush2, kprrel ),


	KB_MATRIX_LAYER(  // press: layer 1: function and symbol keys
// unused
NULL,
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
kprrel,sshprre, kprrel, kprrel,sshprre, kprrel, kprrel,
kprrel, kprrel,sshprre,sshprre,sshprre,sshprre,
ktrans, kprrel,sshprre,sshprre, kprrel,sshprre, kprrel,
 ktrans, kprrel, kprrel, kprrel, kprrel,
                                                 kprrel, kprrel,
                                         kprrel, kprrel, kprrel,
                                         kprrel, kprrel, kprrel,
// right hand
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel,sshprre,sshprre, kprrel, kprrel, kprrel,
               sshprre,sshprre, kprrel,sshprre, kprrel, kprrel,
        kprrel,sshprre,sshprre,sshprre,sshprre,sshprre, kprrel,
                        kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel, NULL,   NULL,
 kprrel, kprrel, kprrel ),


	KB_MATRIX_LAYER(  // press: layer 2: keyboard functions
// unused
kprrel,
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, ktrans,
                                                 kprrel, kprrel,
                                         kprrel, kprrel, kprrel,
                                         kprrel, ktrans, ktrans,
// right hand
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
                        kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel, NULL,   NULL,
 kprrel, ktrans, ktrans ),


	KB_MATRIX_LAYER(  // press: layer 3: numpad
// unused
NULL,
// left hand
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
 ktrans, kprrel, ktrans, ktrans, ktrans,
                                                 ktrans, ktrans,
                                         ktrans, ktrans, ktrans,
                                         ktrans, ktrans, ktrans,
// right hand
       slponum, ktrans,slponum, kprrel, kprrel, kprrel, ktrans,
        ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                        ktrans, ktrans, kprrel, kprrel, ktrans,
 ktrans, ktrans,
 ktrans, ktrans, ktrans,
 ktrans, ktrans, kprrel ),

};

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {

	KB_MATRIX_LAYER(  // release: layer 0: default
// unused
NULL,
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
  lpop1, kprrel, kprrel, kprrel, kprrel, kprrel,
 s2kcap, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel,
                                                 kprrel, kprrel,
                                           NULL,   NULL, kprrel,
                                         kprrel, kprrel, kprrel,
// right hand
          NULL, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel, kprrel, lpop1,
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, s2kcap,
                        lpop2, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel,   NULL,   NULL,
 kprrel,  lpop2, kprrel ),


	KB_MATRIX_LAYER(  // release: layer 1: function and symbol keys
// unused
NULL,
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel,sshprre, kprrel, kprrel,sshprre, kprrel, kprrel,
 kprrel, kprrel,sshprre,sshprre,sshprre,sshprre,
 ktrans, kprrel,sshprre,sshprre, kprrel,sshprre, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel,
                                                 kprrel, kprrel,
                                         kprrel, kprrel, kprrel,
                                         kprrel, kprrel, kprrel,
// right hand
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel,sshprre,sshprre, kprrel, kprrel, kprrel,
               sshprre,sshprre, kprrel,sshprre, kprrel, kprrel,
        kprrel,sshprre,sshprre,sshprre,sshprre,sshprre, kprrel,
                        kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel ),


	KB_MATRIX_LAYER(  // release: layer 2: keyboard functions
// unused
kprrel,
// left hand
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel, kprrel, kprrel, ktrans,
                                                 kprrel, kprrel,
                                         kprrel, kprrel, kprrel,
                                         kprrel, ktrans, ktrans,
// right hand
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        kprrel, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
                        kprrel, kprrel, kprrel, kprrel, kprrel,
 kprrel, kprrel,
 kprrel, kprrel, kprrel,
 kprrel, ktrans, ktrans ),


	KB_MATRIX_LAYER(  // release: layer 3: numpad
// unused
0,
// left hand
 ktrans, ktrans, ktrans, ktrans, ktrans, ktrans, ktrans,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel,
 ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, ktrans,
 ktrans, kprrel, ktrans, ktrans, ktrans,
                                                 ktrans, ktrans,
                                         ktrans, ktrans, ktrans,
                                         ktrans, ktrans, ktrans,
// right hand
          NULL, ktrans,   NULL, kprrel, kprrel, kprrel, ktrans,
        ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
        ktrans, kprrel, kprrel, kprrel, kprrel, kprrel, kprrel,
                        ktrans, ktrans, kprrel, kprrel, ktrans,
 ktrans, ktrans,
 ktrans, ktrans, ktrans,
 ktrans, ktrans, kprrel ),


	KB_MATRIX_LAYER(  // release: layer 3: nothing (just making sure unused
			  // functions don't get compiled out)
// unused
NULL,
// other
 kprrel, lpush8,  lpop8,   NULL,   NULL,   NULL,   NULL,   NULL,
   ktog, lpush9,  lpop9,   NULL,   NULL,   NULL,   NULL,   NULL,
 ktrans,lpush10, lpop10,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush1,  lpop1,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush2,  lpop2, dbtldr,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush3,  lpop3,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush4,  lpop4, s2kcap,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush5,  lpop5,slpunum,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush6,  lpop6,slponum,   NULL,   NULL,   NULL,   NULL,   NULL,
 lpush7,  lpop7,   NULL,   NULL,   NULL,   NULL,   NULL,   NULL )

};
