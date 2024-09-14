CLI           := arduino-cli
FQBN          := esp32-bluepad32:esp32:adafruit_itsybitsy_esp32
BOARD         := esp32-bluepad32:esp32
SKETCH_NAME   := bbrx
SERIAL_PORT   := /dev/ttyACM1
SERIAL_CONFIG := 115200
GIT_HASH      := $(shell git rev-parse --short HEAD)

BOARD_PKG_ESP32 := https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
BOARD_PKG_BP32  := https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json

# default target to build and upload code
all: build upload monitor

# test since i'm using this to learn how to write makefiles
test:
	@echo "bbrx build test"

# install dependancies
setup:
	@$(CLI) core install $(BOARD) --additional-urls $(BOARD_PKG_ESP32),$(BOARD_PKG_BP32)
	@$(CLI) lib install ESP32Servo

# build sketch using arduino-cli
build:
	@$(CLI) compile --fqbn $(FQBN) --build-property build.extra_flags=-DGIT_HASH=\"${GIT_HASH}\" --build-property compiler.cpp.extra_flags=-fexceptions $(SKETCH_NAME)

# upload sketch using arduino-cli
upload:
	@$(CLI) upload -p $(SERIAL_PORT) --fqbn $(FQBN) $(SKETCH_NAME)

# start the serial monitor
monitor:
	@$(CLI) monitor -p $(SERIAL_PORT) --config $(SERIAL_CONFIG) -b $(FQBN)