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

  Layers = [ :basic, :mod3, :mod4, :mod5 ]

  Functions = {
    #            	    	down                                   	up
    "basic"      	=> [	"&kbfun_press_release",                	                    	],
    "toggle"     	=> [	"&kbfun_toggle",                       	                    	],
    "transparent"	=> [	"&kbfun_transparent",                  	                    	],
    #            	    	down                                   	up
    "mod3"       	=> [	"&kbfun_layer_push_1",                 	"&kbfun_layer_pop_1"	],
    "mod4"       	=> [	"&kbfun_layer_push_2",                 	"&kbfun_layer_pop_2"	],
    "mod5"       	=> [	"&kbfun_layer_push_3",                 	"&kbfun_layer_pop_3"	],
    "latch_mod3" 	=> [	"&kbfun_layer_sticky_1",               	                    	],
    "latch_mod4" 	=> [	"&kbfun_layer_sticky_2",               	                    	],
    "latch_mod5" 	=> [	"&kbfun_layer_sticky_3",               	                    	],
    #            	    	down                                   	up
    "shifted"    	=> [	"&kbfun_shift_press_release",          	                    	],
    "ctrled"     	=> [	"&kbfun_control_press_release",        	                    	],
    "capslock"   	=> [	"&kbfun_2_keys_capslock_press_release",	                    	],
  }

  Keys = {
    "a"          	=> "KEY_a_A",
    "b"          	=> "KEY_b_B",
    "c"          	=> "KEY_c_C",
    "d"          	=> "KEY_d_D",
    "e"          	=> "KEY_e_E",
    "f"          	=> "KEY_f_F",
    "g"          	=> "KEY_g_G",
    "h"          	=> "KEY_h_H",
    "i"          	=> "KEY_i_I",
    "j"          	=> "KEY_j_J",
    "k"          	=> "KEY_k_K",
    "l"          	=> "KEY_l_L",
    "m"          	=> "KEY_m_M",
    "n"          	=> "KEY_n_N",
    "o"          	=> "KEY_o_O",
    "p"          	=> "KEY_p_P",
    "q"          	=> "KEY_q_Q",
    "r"          	=> "KEY_r_R",
    "s"          	=> "KEY_s_S",
    "t"          	=> "KEY_t_T",
    "u"          	=> "KEY_u_U",
    "v"          	=> "KEY_v_V",
    "w"          	=> "KEY_w_W",
    "x"          	=> "KEY_x_X",
    "y"          	=> "KEY_y_Y",
    "z"          	=> "KEY_z_Z",
    #            	
    "0"          	=> "KEY_0_RightParenthesis",
    "1"          	=> "KEY_1_Exclamation",
    "2"          	=> "KEY_2_At",
    "3"          	=> "KEY_3_Pound",
    "4"          	=> "KEY_4_Dollar",
    "5"          	=> "KEY_5_Percent",
    "6"          	=> "KEY_6_Caret",
    "7"          	=> "KEY_7_Ampersand",
    "8"          	=> "KEY_8_Asterisk",
    "9"          	=> "KEY_9_LeftParenthesis",
    #            	
    "f1"         	=> "KEY_F1",
    "f2"         	=> "KEY_F2",
    "f3"         	=> "KEY_F3",
    "f4"         	=> "KEY_F4",
    "f5"         	=> "KEY_F5",
    "f6"         	=> "KEY_F6",
    "f7"         	=> "KEY_F7",
    "f8"         	=> "KEY_F8",
    "f9"         	=> "KEY_F9",
    "f10"        	=> "KEY_F10",
    "f11"        	=> "KEY_F11",
    "f12"        	=> "KEY_F12",
    "f13"        	=> "KEY_F13",
    "f14"        	=> "KEY_F14",
    "f15"        	=> "KEY_F15",
    "f16"        	=> "KEY_F16",
    "f17"        	=> "KEY_F17",
    "f18"        	=> "KEY_F18",
    "f19"        	=> "KEY_F19",
    "f20"        	=> "KEY_F20",
    "f21"        	=> "KEY_F21",
    "f22"        	=> "KEY_F22",
    "f23"        	=> "KEY_F23",
    "f24"        	=> "KEY_F24",
    #            	
    "\\"         	=> "KEY_Backslash_Pipe",
    "{"          	=> "KEY_LeftBracket_LeftBrace",
    "}"          	=> "KEY_RightBracket_RightBrace",
    "["          	=> "KEY_LeftBracket_LeftBrace",
    "]"          	=> "KEY_RightBracket_RightBrace",
    ","          	=> "KEY_Comma_LessThan",
    "-"          	=> "KEY_Dash_Underscore",
    "="          	=> "KEY_Equal_Plus",
    "`"          	=> "KEY_GraveAccent_Tilde",
    "."          	=> "KEY_Period_GreaterThan",
    "\'"         	=> "KEY_SingleQuote_DoubleQuote",
    ";"          	=> "KEY_Semicolon_Colon",
    "/"          	=> "KEY_Slash_Question",
    "~"          	=> "KEY_GraveAccent_Tilde",
    "%"          	=> "KEY_5_Percent",
    "*"          	=> "KEY_8_Asterisk",
    ":"          	=> "KEY_Semicolon_Colon",
    "^"          	=> "KEY_6_Caret",
    "<"          	=> "KEY_Comma_LessThan",
    ">"          	=> "KEY_Period_GreaterThan",
    "?"          	=> "KEY_Slash_Question",
    "!"          	=> "KEY_1_Exclamation",
    "("          	=> "KEY_9_LeftParenthesis",
    ")"          	=> "KEY_0_RightParenthesis",
    "|"          	=> "KEY_Backslash_Pipe",
    "@"          	=> "KEY_2_At",
    "\""         	=> "KEY_SingleQuote_DoubleQuote",
    "_"          	=> "KEY_Dash_Underscore",
    "+"          	=> "KEY_Equal_Plus",
    "$"          	=> "KEY_4_Dollar",
    "&"          	=> "KEY_7_Ampersand",
    "#"          	=> "KEY_3_Pound",
    "hash"       	=> "KEY_3_Pound",
    #            	
    "enter"      	=> "KEY_ReturnEnter",
    "return"     	=> "KEY_ReturnEnter",
    "space"      	=> "KEY_Spacebar",
    "tab"        	=> "KEY_Tab",
    "backspace"  	=> "KEY_DeleteBackspace",
    "delete"     	=> "KEY_DeleteForward",
    "home"       	=> "KEY_Home",
    "end"        	=> "KEY_End",
    "page_up"    	=> "KEY_PageUp",
    "page_down"  	=> "KEY_PageDown",
    "up"         	=> "KEY_UpArrow",
    "down"       	=> "KEY_DownArrow",
    "left"       	=> "KEY_LeftArrow",
    "right"      	=> "KEY_RightArrow",
    "escape"     	=> "KEY_Escape",
    "insert"     	=> "KEY_Insert",
    "menu"       	=> "KEY_Application",
    #            	
    "alt"        	=> "KEY_LeftAlt",
    "alt_gr"     	=> "KEY_RightAlt",
    "umlaut"     	=> "KEY_RightAlt",
    "control"    	=> "KEY_LeftControl",
    "control_l"  	=> "KEY_LeftControl",
    "control_r"  	=> "KEY_RightControl",
    "win"        	=> "KEY_LeftGUI",
    "shift_l"    	=> "KEY_LeftShift",
    "shift_r"    	=> "KEY_RightShift",
    "scroll_lock"	=> "KEY_ScrollLock",
    #            	
    "mod3"       	=> "1",
    "mod4"       	=> "2",
    "mod5"       	=> "3",
    #            	
    "NULL"       	=> "NULL",
  }

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
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
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

keys_string =<<EOL

[╳1 # L FINGERS (1 to 27?)
#	┰	0      	        	┰	1     	       	┰	2        	       	┰	3        	       	┰	4     	       	┰	5     	       	┰	6    		#      	
 	┃	0      	        	┃	1     	       	┃	2        	       	┃	3        	       	┃	4     	       	┃	5     	       	┃	6    		# basic	
 	┃	f11    	        	┃	f1    	       	┃	f2       	       	┃	f3       	       	┃	f4    	       	┃	f5    	       	┃	f6   		# pun  	
 	┃	f11    	        	┃	f1    	       	┃	f2       	       	┃	f3       	       	┃	f4    	       	┃	f5    	       	┃	f6   		# nav  	
 	┃	f11    	        	┃	f1    	       	┃	f2       	       	┃	f3       	       	┃	f4    	       	┃	f5    	       	┃	f6   		# funk 	
#	┰	◼      	        	┰	x     	       	┰	v        	       	┰	l        	       	┰	c     	       	┰	w     	       	┰	◼    		#      	
 	┃	x      	        	┃	x     	       	┃	v        	       	┃	l        	       	┃	c     	       	┃	w     	       	┃	tab  		# basic	
 	┃	~      	shifted 	┃	~     	shifted	┃	[        	       	┃	'        	       	┃	<     	shifted	┃	\\    	       	┃	     		# pun  	
 	┃	escape 	        	┃	escape	       	┃	backspace	       	┃	enter    	       	┃	delete	       	┃	insert	       	┃	     		# nav  	
 	┃	       	        	┃	      	       	┃	         	       	┃	         	       	┃	      	       	┃	      	       	┃	     		# funk 	
#	┰	◼      	        	┰	u     	       	┰	i        	       	┰	a        	       	┰	e     	       	┰	o     	       	 	     		#      	
 	┃	umlaut 	        	┃	u     	       	┃	i        	       	┃	a        	       	┃	e     	       	┃	o     	       	 	     		# basic	
 	┃	       	        	┃	,     	       	┃	\{       	shifted	┃	?        	shifted	┃	!     	shifted	┃	(     	shifted	 	     		# pun  	
 	┃	       	        	┃	left  	       	┃	up       	       	┃	down     	       	┃	right 	       	┃	tab   	       	 	     		# nav  	
 	┃	       	        	┃	      	       	┃	         	       	┃	         	       	┃	      	       	┃	      	       	 	     		# funk 	
#	┰	◼      	        	┰	%     	       	┰	*        	       	┰	:        	       	┰	p     	       	┰	z     	       	┰	◼    		#      	
 	┃	shift_l	capslock	┃	%     	shifted	┃	*        	shifted	┃	:        	shifted	┃	p     	       	┃	z     	       	┃	enter		# basic	
 	┃	       	        	┃	`     	       	┃	^        	shifted	┃	|        	shifted	┃	-     	       	┃	@     	shifted	┃	     		# pun  	
 	┃	       	        	┃	home  	       	┃	page_up  	       	┃	page_down	       	┃	end   	       	┃	      	       	┃	     		# nav  	
 	┃	       	        	┃	      	       	┃	         	       	┃	         	       	┃	      	       	┃	      	       	┃	     		# funk 	]

[╳2 # L UNDER (? to ?)
#	┰	◼   		┰	◼ 		┰	◼   		┰	◼    		#      	
 	┃	left		┃	up		┃	down		┃	right		# basic	
 	┃	    		┃	  		┃	    		┃	     		# pun  	
 	┃	    		┃	  		┃	    		┃	     		# nav  	
 	┃	    		┃	  		┃	    		┃	     		# funk 	]

[╳3 # L UNDERTHUMB (? to ?)
#	┰	◼  		#      	
 	┃	win		# basic	
 	┃	   		# pun  	
 	┃	   		# nav  	
 	┃	   		# funk 	]

[╳4 # L THUMB (? to ?)
#	 	     		┰	b3         		┰	c3         		#      	
 	 	     		┃	scroll_lock		┃	scroll_lock		# basic	
 	 	     		┃	           		┃	           		# pun  	
 	 	     		┃	           		┃	           		# nav  	
 	 	     		┃	           		┃	           		# funk 	
#	┰	a2*  		┰	b2*        		┰	c2         		#      	
 	┃	space		┃	control    		┃	alt        		# basic	
 	┃	     		┃	           		┃	           		# pun  	
 	┃	     		┃	           		┃	           		# nav  	
 	┃	     		┃	           		┃	           		# funk 	
#	┰	a1   		┰	b1         		┰	c1         		#      	
 	┃	space		┃	control    		┃	alt        		# basic	
 	┃	     		┃	           		┃	           		# pun  	
 	┃	     		┃	           		┃	           		# nav  	
 	┃	     		┃	           		┃	           		# funk 	]

[╳5 # R FINGERS (? to ?)
#	┰	5    		┰	6 	       	┰	7  	       	┰	8  	       	┰	9   	       	┰	0  	       	┰	0      	        	#      	
 	┃	5    		┃	6 	       	┃	7  	       	┃	8  	       	┃	9   	       	┃	0  	       	┃	0      	        	# basic	
 	┃	f5   		┃	f6	       	┃	f7 	       	┃	f8 	       	┃	f9  	       	┃	f10	       	┃	f12    	        	# pun  	
 	┃	f5   		┃	f6	       	┃	f7 	       	┃	f8 	       	┃	f9  	       	┃	f10	       	┃	f12    	        	# nav  	
 	┃	f5   		┃	f6	       	┃	f7 	       	┃	f8 	       	┃	f9  	       	┃	f10	       	┃	f12    	        	# funk 	
#	┰	◼    		┰	k 	       	┰	h  	       	┰	g  	       	┰	f   	       	┰	q  	       	┰	◼      	        	#      	
 	┃	     		┃	k 	       	┃	h  	       	┃	g  	       	┃	f   	       	┃	q  	       	┃	q      	        	# basic	
 	┃	     		┃	= 	       	┃	>  	shifted	┃	"  	shifted	┃	]   	       	┃	`  	       	┃	`      	        	# pun  	
 	┃	     		┃	  	       	┃	f21	       	┃	f22	       	┃	f23 	       	┃	f24	       	┃	       	        	# nav  	
 	┃	     		┃	  	       	┃	   	       	┃	   	       	┃	    	       	┃	   	       	┃	       	        	# funk 	
#	 	     		┰	s 	       	┰	n  	       	┰	r  	       	┰	t   	       	┰	d  	       	┰	◼      	        	#      	
 	 	     		┃	s 	       	┃	n  	       	┃	r  	       	┃	t   	       	┃	d  	       	┃	umlaut 	        	# basic	
 	 	     		┃	) 	shifted	┃	_  	shifted	┃	/  	       	┃	\}  	shifted	┃	.  	       	┃	       	        	# pun  	
 	 	     		┃	  	       	┃	f13	       	┃	f14	       	┃	f15 	       	┃	f16	       	┃	       	        	# nav  	
 	 	     		┃	  	       	┃	   	       	┃	   	       	┃	    	       	┃	   	       	┃	       	        	# funk 	
#	┰	◼    		┰	b 	       	┰	   	       	┰	j  	       	┰	y   	       	┰	;  	       	┰	◼      	        	#      	
 	┃	enter		┃	b 	       	┃	m  	       	┃	j  	       	┃	y   	       	┃	;  	       	┃	shift_r	capslock	# basic	
 	┃	     		┃	+ 	shifted	┃	$  	shifted	┃	&  	shifted	┃	hash	shifted	┃	^  	shifted	┃	       	        	# pun  	
 	┃	     		┃	  	       	┃	f17	       	┃	f18	       	┃	f19 	       	┃	f20	       	┃	       	        	# nav  	
 	┃	     		┃	  	       	┃	   	       	┃	   	       	┃	    	       	┃	   	       	┃	       	        	# funk 	]

[╳6 # R UNDERTHUMB (? to ?)
#				┰	◼   	    	#	
 				┃	mod4	mod4	 	# basic	
 				┃	    	    	 	# pun  	
 				┃	    	    	 	# nav  	
 				┃	    	    	 	# funk 	]

[╳7 # R UNDER (? to ?)
#	┰	◼   		┰	◼ 		┰	◼   		┰	◼    		#      	
 	┃	left		┃	up		┃	down		┃	right		# basic	
 	┃	    		┃	  		┃	    		┃	     		# pun  	
 	┃	    		┃	  		┃	    		┃	     		# nav  	
 	┃	    		┃	  		┃	    		┃	     		# funk 	]

[╳8 # R THUMB (? to ?)
#	┰	c3  		┰	b3 		 	    	          	#      	
 	┃	    		┃	   		 	    	          	# basic	
 	┃	    		┃	   		 	    	          	# pun  	
 	┃	    		┃	   		 	    	          	# nav  	
 	┃	    		┃	   		 	    	          	# funk 	
#	┰	c2  		┰	b2*		┰	a2* 	          	#      	
 	┃	menu		┃	alt		┃	mod3	latch_mod3	# basic	
 	┃	    		┃	   		┃	mod3	mod3      	# pun  	
 	┃	    		┃	   		┃	NULL	          	# nav  	
 	┃	    		┃	   		┃	NULL	          	# funk 	
#	┰	c1  		┰	b1 		┰	a1  	          	#      	
 	┃	menu		┃	alt		┃	mod3	latch_mod3	# basic	
 	┃	    		┃	   		┃	mod3	mod3      	# pun  	
 	┃	    		┃	   		┃	NULL	          	# nav  	
 	┃	    		┃	   		┃	NULL	          	# funk 	]
EOL

groups	= keys_string.gsub(/#.*$/, '').split(/\[╳/).reject(&:blank?).map(&:lines)
groups	= groups.sort_by(&:first)
groups	= groups.map{|g| g.drop(1).reject(&:blank?)}

keys_parsed = [
  # dummy key
  Key::Layers.map{[]}
]

groups.each do |group|
  layers = Key::Layers.size

  # sanity check
  raise "wrong number of key layers" if group.size % layers != 0

  slices = group.map{|l| l.split("┃").drop(1)}

  (0..(group.size-1)).step(layers).each do |row|
    slices[row].size.times do |col|
      key = layers.times.map do |layer|
        slices[row+layer][col]
      end
      key = key.map{|l| l.strip.split(/\s+/, 2)}

      keys_parsed << key
    end
  end
end

keys = keys_parsed.map do |layers|
  Key.new layers
end

saneo = Layout.new :saneo, keys
saneo.save! LayoutFile
