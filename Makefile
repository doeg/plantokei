# For a list of all variables that can be overridden, see:
# 		https://github.com/sudar/Arduino-Makefile/blob/master/arduino-mk-vars.md

ARDUINO_DIR   = $(HOME)/Applications/Arduino.app/Contents/Java
ARDMK_DIR     = $(realpath ./libraries/Arduino-Makefile)
MONITOR_PORT  = /dev/cu.usb*
BOARD_TAG     = uno

ARDUINO_LIBS  = SPI Adafruit-GFX-Library Adafruit-ST7735-Library
USER_LIB_PATH =  $(realpath ./libraries)

MONITOR_BAUDRATE  = 9600

AVR_TOOLS_DIR = /usr/local
AVRDUDE = /usr/local/bin/avrdude

CFLAGS_STD = -std=gnu11
CXXFLAGS_STD = -std=gnu++11
CXXFLAGS = -pedantic -Wall -Wextra

OBJDIR = $(realpath ./build)

include $(ARDMK_DIR)/Arduino.mk