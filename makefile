# -----------------------------------------------------------------------------
# makefile for the ergoDOX project
# -----------------------------------------------------------------------------

# directories
BUILD := build
ROOT := $(BUILD)/$(TARGET)
SCRIPTS := build-scripts

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

.PHONY: all clean firmware

all: firmware

clean:
	cd src; $(MAKE) clean

firmware: clean
	cd src; $(MAKE) all
