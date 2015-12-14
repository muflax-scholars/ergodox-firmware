# -----------------------------------------------------------------------------
# makefile for the ergoDOX project
# -----------------------------------------------------------------------------

.PHONY: all clean firmware layout

all: firmware

clean:
	cd src; $(MAKE) clean

firmware: clean layout
	cd src; $(MAKE) all

layout:
	./generate_layout.rb
