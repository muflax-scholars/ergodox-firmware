#!/usr/bin/env ruby
# -*- encoding: utf-8 -*-
# Copyright muflax <mail@muflax.com>, 2015
# License: GNU GPLv3 (or later) <http://www.gnu.org/copyleft/gpl.html>

require "muflax"

LayoutDir 	= "src/keyboard/ergodox/layout"
LayoutFile	= "#{LayoutDir}/saneo-mod.c"

puts "generating #{LayoutFile}..."

Layer = Struct.new :code, :up, :down

class Key
  attr_reader :layers

  Layers = [ :basic, :punc, :nav, :func ]

  Functions = {
    #            	    	down                                   	up
    "basic"      	=> [	"&kbfun_press_release",                	                      	],
    "media"      	=> [	"&kbfun_mediakey_press_release",       	                      	],
    "toggle"     	=> [	"&kbfun_toggle",                       	                      	],
    "transparent"	=> [	"&kbfun_transparent",                  	                      	],
    #            	    	down                                   	up
    "layer"      	=> [	"&kbfun_layer_enable",                 	"&kbfun_layer_disable"	],
    "latch"      	=> [	"&kbfun_layer_sticky",                 	                      	],
    #            	    	down                                   	up
    "shifted"    	=> [	"&kbfun_shift_press_release",          	                      	],
    "ctrled"     	=> [	"&kbfun_control_press_release",        	                      	],
    "capslock"   	=> [	"&kbfun_2_keys_capslock_press_release",	                      	],
  }

  Keys = {
    "a"                	=> "KEY_a_A",
    "b"                	=> "KEY_b_B",
    "c"                	=> "KEY_c_C",
    "d"                	=> "KEY_d_D",
    "e"                	=> "KEY_e_E",
    "f"                	=> "KEY_f_F",
    "g"                	=> "KEY_g_G",
    "h"                	=> "KEY_h_H",
    "i"                	=> "KEY_i_I",
    "j"                	=> "KEY_j_J",
    "k"                	=> "KEY_k_K",
    "l"                	=> "KEY_l_L",
    "m"                	=> "KEY_m_M",
    "n"                	=> "KEY_n_N",
    "o"                	=> "KEY_o_O",
    "p"                	=> "KEY_p_P",
    "q"                	=> "KEY_q_Q",
    "r"                	=> "KEY_r_R",
    "s"                	=> "KEY_s_S",
    "t"                	=> "KEY_t_T",
    "u"                	=> "KEY_u_U",
    "v"                	=> "KEY_v_V",
    "w"                	=> "KEY_w_W",
    "x"                	=> "KEY_x_X",
    "y"                	=> "KEY_y_Y",
    "z"                	=> "KEY_z_Z",
    #                  	
    "0"                	=> "KEY_0_RightParenthesis",
    "1"                	=> "KEY_1_Exclamation",
    "2"                	=> "KEY_2_At",
    "3"                	=> "KEY_3_Pound",
    "4"                	=> "KEY_4_Dollar",
    "5"                	=> "KEY_5_Percent",
    "6"                	=> "KEY_6_Caret",
    "7"                	=> "KEY_7_Ampersand",
    "8"                	=> "KEY_8_Asterisk",
    "9"                	=> "KEY_9_LeftParenthesis",
    #                  	
    "f1"               	=> "KEY_F1",
    "f2"               	=> "KEY_F2",
    "f3"               	=> "KEY_F3",
    "f4"               	=> "KEY_F4",
    "f5"               	=> "KEY_F5",
    "f6"               	=> "KEY_F6",
    "f7"               	=> "KEY_F7",
    "f8"               	=> "KEY_F8",
    "f9"               	=> "KEY_F9",
    "f10"              	=> "KEY_F10",
    "f11"              	=> "KEY_F11",
    "f12"              	=> "KEY_F12",
    "f13"              	=> "KEY_F13",
    "f14"              	=> "KEY_F14",
    "f15"              	=> "KEY_F15",
    "f16"              	=> "KEY_F16",
    "f17"              	=> "KEY_F17",
    "f18"              	=> "KEY_F18",
    "f19"              	=> "KEY_F19",
    "f20"              	=> "KEY_F20",
    "f21"              	=> "KEY_F21",
    "f22"              	=> "KEY_F22",
    "f23"              	=> "KEY_F23",
    "f24"              	=> "KEY_F24",
    #                  	
    "\\"               	=> "KEY_Backslash_Pipe",
    "{"                	=> "KEY_LeftBracket_LeftBrace",
    "}"                	=> "KEY_RightBracket_RightBrace",
    "["                	=> "KEY_LeftBracket_LeftBrace",
    "]"                	=> "KEY_RightBracket_RightBrace",
    ","                	=> "KEY_Comma_LessThan",
    "-"                	=> "KEY_Dash_Underscore",
    "="                	=> "KEY_Equal_Plus",
    "`"                	=> "KEY_GraveAccent_Tilde",
    "."                	=> "KEY_Period_GreaterThan",
    "\'"               	=> "KEY_SingleQuote_DoubleQuote",
    ";"                	=> "KEY_Semicolon_Colon",
    "/"                	=> "KEY_Slash_Question",
    "~"                	=> "KEY_GraveAccent_Tilde",
    "%"                	=> "KEY_5_Percent",
    "*"                	=> "KEY_8_Asterisk",
    ":"                	=> "KEY_Semicolon_Colon",
    "^"                	=> "KEY_6_Caret",
    "<"                	=> "KEY_Comma_LessThan",
    ">"                	=> "KEY_Period_GreaterThan",
    "?"                	=> "KEY_Slash_Question",
    "!"                	=> "KEY_1_Exclamation",
    "("                	=> "KEY_9_LeftParenthesis",
    ")"                	=> "KEY_0_RightParenthesis",
    "|"                	=> "KEY_Backslash_Pipe",
    "@"                	=> "KEY_2_At",
    "\""               	=> "KEY_SingleQuote_DoubleQuote",
    "_"                	=> "KEY_Dash_Underscore",
    "+"                	=> "KEY_Equal_Plus",
    "$"                	=> "KEY_4_Dollar",
    "&"                	=> "KEY_7_Ampersand",
    "#"                	=> "KEY_3_Pound",
    #                  	
    "enter"            	=> "KEY_ReturnEnter",
    "return"           	=> "KEY_ReturnEnter",
    "space"            	=> "KEY_Spacebar",
    "tab"              	=> "KEY_Tab",
    "backspace"        	=> "KEY_DeleteBackspace",
    "delete"           	=> "KEY_DeleteForward",
    "home"             	=> "KEY_Home",
    "end"              	=> "KEY_End",
    "page_up"          	=> "KEY_PageUp",
    "page_down"        	=> "KEY_PageDown",
    "up"               	=> "KEY_UpArrow",
    "down"             	=> "KEY_DownArrow",
    "left"             	=> "KEY_LeftArrow",
    "right"            	=> "KEY_RightArrow",
    "escape"           	=> "KEY_Escape",
    "insert"           	=> "KEY_Insert",
    "menu"             	=> "KEY_Application",
    #                  	
    "alt"              	=> "KEY_LeftAlt",
    "alt_gr"           	=> "KEY_RightAlt",
    "umlaut"           	=> "KEY_RightAlt",
    "control"          	=> "KEY_LeftControl",
    "control_l"        	=> "KEY_LeftControl",
    "control_r"        	=> "KEY_RightControl",
    "win"              	=> "KEY_LeftGUI",
    "shift_l"          	=> "KEY_LeftShift",
    "shift_r"          	=> "KEY_RightShift",
    "scroll_lock"      	=> "KEY_ScrollLock",
    #                  	
    "NULL"             	=> "NULL",
    #                  	
    "audio_mute"       	=> "MEDIAKEY_AUDIO_MUTE",
    "audio_vol_up"     	=> "MEDIAKEY_AUDIO_VOL_UP",
    "audio_vol_down"   	=> "MEDIAKEY_AUDIO_VOL_DOWN",
    "next_track"       	=> "MEDIAKEY_NEXT_TRACK",
    "prev_track"       	=> "MEDIAKEY_PREV_TRACK",
    "stop"             	=> "MEDIAKEY_STOP",
    "play_pause"       	=> "MEDIAKEY_PLAY_PAUSE",
    "record"           	=> "MEDIAKEY_RECORD",
    "rewind"           	=> "MEDIAKEY_REWIND",
    "eject"            	=> "MEDIAKEY_EJECT",
    "cc_config"        	=> "MEDIAKEY_CC_CONFIG",
    "email"            	=> "MEDIAKEY_EMAIL",
    "calculator"       	=> "MEDIAKEY_CALCULATOR",
    "local_browser"    	=> "MEDIAKEY_LOCAL_BROWSER",
    "browser_search"   	=> "MEDIAKEY_BROWSER_SEARCH",
    "browser_home"     	=> "MEDIAKEY_BROWSER_HOME",
    "browser_back"     	=> "MEDIAKEY_BROWSER_BACK",
    "browser_forward"  	=> "MEDIAKEY_BROWSER_FORWARD",
    "browser_stop"     	=> "MEDIAKEY_BROWSER_STOP",
    "browser_refresh"  	=> "MEDIAKEY_BROWSER_REFRESH",
    "browser_bookmarks"	=> "MEDIAKEY_BROWSER_BOOKMARKS",
  }

  Layers.each.with_index do |layer, i|
    Keys["#{layer}"] = "#{i}"
  end

  def initialize layers
    @layers = layers.map do |key, type|
      raise "key not found: #{key}"  	if not Keys.include? key      	and not key.nil?
      raise "type not found: #{type}"	if not Functions.include? type	and not type.nil?

      # just fall through by default
      type    	= "transparent"  	if type.nil? and key.nil?
      key     	= Keys[key]      	|| "NULL"
      up, down	= Functions[type]	|| Functions["basic"]
      down    	||= up

      Layer.new key, down, up
    end
  end
end

class Layout
  def initialize name, keys
    @name	= name
    @keys	= keys
  end

  def keys_to_matrix method
    Key::Layers.map.with_index do |_, layer|
      "KB_MATRIX_LAYER(\n#{@keys.map{|key| key.layers[layer].send(method)}.join(",\n")}),\n"
    end.join("\n")
  end

  def save! file
    puts "saving #{@name}..."

    header =<<HEADER
// ----------------------------------------------------------------------------
// ergoDOX layout : saneo (generated)
// ----------------------------------------------------------------------------
#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"
// ----------------------------------------------------------------------------

HEADER

    keys 	= keys_to_matrix :code
    downs	= keys_to_matrix :down
    ups  	= keys_to_matrix :up

    File.save(LayoutFile) do |f|
      f.puts header
      f.puts "const uint8_t       PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS]         = { #{keys}  };"
      f.puts "const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS]   = { #{downs} };"
      f.puts "const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = { #{ups}   };"
    end
  end
end

keys = [
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	
  %w{	            	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# dummy key
  #  	            	        	      	    	       	      	         	     	      	    	    	  	
  #  	left hand   	        	      	    	       	      	         	     	      	    	    	  	
  #  	number      	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	0           	        	}, %w{	f11 	       	}, %w{	f11      	     	}, %w{	f11 	    	},	# 1.5
  %w{	1           	        	}, %w{	f1  	       	}, %w{	f1       	     	}, %w{	f1  	    	},
  %w{	2           	        	}, %w{	f2  	       	}, %w{	f2       	     	}, %w{	f2  	    	},
  %w{	3           	        	}, %w{	f3  	       	}, %w{	f3       	     	}, %w{	f3  	    	},
  %w{	4           	        	}, %w{	f4  	       	}, %w{	f4       	     	}, %w{	f4  	    	},
  %w{	5           	        	}, %w{	f5  	       	}, %w{	f5       	     	}, %w{	f5  	    	},
  %w{	6           	        	}, %w{	f6  	       	}, %w{	f6       	     	}, %w{	f6  	    	},
  #  	top         	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	x           	        	}, %w{	~   	shifted	}, %w{	escape   	     	}, %w{	    	    	},	# 1.5
  %w{	x           	        	}, %w{	~   	shifted	}, %w{	escape   	     	}, %w{	    	    	},
  %w{	v           	        	}, %w{	[   	       	}, %w{	backspace	     	}, %w{	    	    	},
  %w{	l           	        	}, %w{	'   	       	}, %w{	enter    	     	}, %w{	    	    	},
  %w{	c           	        	}, %w{	<   	shifted	}, %w{	delete   	     	}, %w{	    	    	},
  %w{	w           	        	}, %w{	\\  	       	}, %w{	insert   	     	}, %w{	    	    	},
  %w{	tab         	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  #  	home        	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	umlaut      	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  %w{	u           	        	}, %w{	,   	       	}, %w{	left     	     	}, %w{	f1  	    	},
  %w{	i           	        	}, %w{	\{  	shifted	}, %w{	up       	     	}, %w{	f1  	    	},
  %w{	a           	        	}, %w{	?   	shifted	}, %w{	down     	     	}, %w{	f1  	    	},
  %w{	e           	        	}, %w{	!   	shifted	}, %w{	right    	     	}, %w{	f1  	    	},
  %w{	o           	        	}, %w{	(   	shifted	}, %w{	tab      	     	}, %w{	f1  	    	},
  #  	bottom      	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	shift_l     	capslock	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  %w{	%           	shifted 	}, %w{	`   	       	}, %w{	home     	     	}, %w{	    	    	},
  %w{	*           	shifted 	}, %w{	^   	shifted	}, %w{	page_up  	     	}, %w{	    	    	},
  %w{	:           	shifted 	}, %w{	|   	shifted	}, %w{	page_down	     	}, %w{	    	    	},
  %w{	p           	        	}, %w{	-   	       	}, %w{	end      	     	}, %w{	    	    	},
  %w{	z           	        	}, %w{	@   	shifted	}, %w{	         	     	}, %w{	    	    	},
  %w{	enter       	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  #  	underbottom 	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	left        	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	up          	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	down        	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	right       	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	win         	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  #  	thumb-top   	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	scroll_lock 	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	func        	layer   	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  #  	thumb-double	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	space       	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	control     	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	alt         	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  #  	thumb-home  	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	space       	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	control     	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	alt         	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  #  	            	        	      	    	       	      	         	     	      	    	    	  	
  #  	right hand  	        	      	    	       	      	         	     	      	    	    	  	
  #  	            	        	      	    	       	      	         	     	      	    	    	  	
  #  	number      	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	5           	        	}, %w{	f5  	       	}, %w{	f5       	     	}, %w{	f5  	    	},	# 1.5
  %w{	6           	        	}, %w{	f6  	       	}, %w{	f6       	     	}, %w{	f6  	    	},
  %w{	7           	        	}, %w{	f7  	       	}, %w{	f7       	     	}, %w{	f7  	    	},
  %w{	8           	        	}, %w{	f8  	       	}, %w{	f8       	     	}, %w{	f8  	    	},
  %w{	9           	        	}, %w{	f9  	       	}, %w{	f9       	     	}, %w{	f9  	    	},
  %w{	0           	        	}, %w{	f10 	       	}, %w{	f10      	     	}, %w{	f10 	    	},
  %w{	0           	        	}, %w{	f12 	       	}, %w{	f12      	     	}, %w{	f12 	    	},
  #  	top         	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	            	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  %w{	k           	        	}, %w{	=   	       	}, %w{	9        	     	}, %w{	    	    	},
  %w{	h           	        	}, %w{	>   	shifted	}, %w{	5        	     	}, %w{	    	    	},
  %w{	g           	        	}, %w{	"   	shifted	}, %w{	6        	     	}, %w{	    	    	},
  %w{	f           	        	}, %w{	]   	       	}, %w{	7        	     	}, %w{	    	    	},
  %w{	q           	        	}, %w{	`   	       	}, %w{	8        	     	}, %w{	    	    	},
  %w{	q           	        	}, %w{	`   	       	}, %w{	8        	     	}, %w{	    	    	},	# 1.5
  #  	home        	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	s           	        	}, %w{	)   	shifted	}, %w{	0        	     	}, %w{	    	    	},
  %w{	n           	        	}, %w{	_   	shifted	}, %w{	1        	     	}, %w{	    	    	},
  %w{	r           	        	}, %w{	/   	       	}, %w{	2        	     	}, %w{	    	    	},
  %w{	t           	        	}, %w{	\}  	shifted	}, %w{	3        	     	}, %w{	    	    	},
  %w{	d           	        	}, %w{	.   	       	}, %w{	4        	     	}, %w{	    	    	},
  %w{	umlaut      	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  #  	bottom      	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	enter       	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  %w{	b           	        	}, %w{	+   	shifted	}, %w{	9        	     	}, %w{	    	    	},
  %w{	m           	        	}, %w{	$   	shifted	}, %w{	5        	     	}, %w{	    	    	},
  %w{	j           	        	}, %w{	&   	shifted	}, %w{	6        	     	}, %w{	    	    	},
  %w{	y           	        	}, %w{	#   	shifted	}, %w{	7        	     	}, %w{	    	    	},
  %w{	;           	        	}, %w{	^   	shifted	}, %w{	8        	     	}, %w{	    	    	},
  %w{	shift_r     	capslock	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},	# 1.5
  #  	underbottom 	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	nav         	layer   	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	left        	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	up          	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	down        	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	right       	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  #  	thumb-top   	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	punc        	layer   	}, %w{	    	       	}, %w{	func     	layer	}, %w{	    	    	},
  %w{	nav         	layer   	}, %w{	func	layer  	}, %w{	         	     	}, %w{	    	    	},
  #  	thumb-double	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	menu        	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	alt         	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	punc        	latch   	}, %w{	punc	layer  	}, %w{	NULL     	     	}, %w{	NULL	    	},
  #  	thumb-home  	        	      	    	       	      	         	     	      	    	    	  	
  #  	letter      	type    	      	punc	type   	      	nav      	type 	      	func	type	  	
  %w{	menu        	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	alt         	        	}, %w{	    	       	}, %w{	         	     	}, %w{	    	    	},
  %w{	punc        	latch   	}, %w{	punc	layer  	}, %w{	NULL     	     	}, %w{	NULL	    	},

].each_slice(Key::Layers.size).map do |layers|
  Key.new layers
end

saneo = Layout.new :saneo, keys
saneo.save! LayoutFile
