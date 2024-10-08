#pragma once

/*
 * bbrx config file
 *
 * please note that some config items are #defined since they will never change
 * over the run time of the program.  however some programs are declared as (extern)
 * variables and implemented in config.cpp.  This is because these variables are
 * intended to be overridden after the bbrx config file is loaded.  In the case that
 * the config file is not loaded, the default values provided in config.cpp are used.
 * 
*/

#include <vector>
#include "event_manager.h"

//-------------------------------------------
//  General System Stuff
//-------------------------------------------

#define VERSION_STRING          "v1.1"


//-------------------------------------------
// ESC PWM settings
//-------------------------------------------

#define ESC_PWM_MIN             1000    // minimum pulse width in µs
#define ESC_PWM_MID             1500    // half-way pulse width in µs
#define ESC_PWM_MAX             2000    // maximum pulse width in µs
#define ESC_PWM_FREQ            50      // pwm frequency in Hz

//-------------------------------------------
// config.yml loading settings
//-------------------------------------------

#define CONFIG_FILE_PATH            "/config.yml"   // the path to the config file

// #define CONFIG_ENABLE_SD                            // enable checking the SD card for config.yml
#define CONFIG_SD_PIN_MISO          27
#define CONFIG_SD_PIN_MOSI          13
#define CONFIG_SD_PIN_SCLK          14
#define CONFIG_SD_PIN_CS            25
#define CONFIG_SD_SPI_FREQ          10000

#define CONFIG_ENABLE_LITTLEFS                      // enable checking littlefs for config.yml
#define CONFIG_LFS_FORMAT_IF_FAIL   true            // whether to format the littlefs partition if it fails to init
#define CONFIG_LFS_BASE_PATH        "/littlefs"     // base path at which to mount fs
#define CONFIG_LFS_MAX_OPEN_FILES   10              // maximum number of open files at any given time
#define CONFIG_LFS_PARTITION_LABEL  "spiffs"        // label of the flash partition to use

// function to load config file
bool load_config();


//-------------------------------------------
// failsafes
//-------------------------------------------

// you can globally disable all failsafes by commenting out ENABLE_FAILSAFES,
// or you can disable specific failsafes by uncommenting their specific define
#define ENABLE_FAILSAFES                // when defined, failsafes will be enabled.  PLEASE DON'T DISABLE THIS UNLESS YOU REALLY REALLY REALLY NEED TO!!!!!!!PLEASE
#define FAILSAFE_NO_CONTROLLER          // enables the failsafe where if no controllers are detected, the motors will be killed


//-------------------------------------------
//  Bot Control Settings
//-------------------------------------------

// vector storing all bindings
extern std::vector<bb_binding> bindings;

// Deadzones and Beefzones
// each binding specifies a minimum and maximum value for the input range
// deadzone is the value below which the input defaults to 0
// beefzone is the value above which the input defaults to max(range_min, range_max), _and_
//             the value _below_ which the input defaults to min(range_min, range_max)

extern int32_t DEADZONE_LY;         // inner deadzone for the left analog stick y axis
extern int32_t BEEFZONE_LY;         // outer deadzone for the left analog stick y axis
extern int32_t DEADZONE_LX;         // inner deadzone for the left analog stick x axis
extern int32_t BEEFZONE_LX;         // outer deadzone for the left analog stick x axis

extern int32_t DEADZONE_RY;         // inner deadzone for the left analog stick y axis
extern int32_t BEEFZONE_RY;         // outer deadzone for the left analog stick y axis
extern int32_t DEADZONE_RX;         // inner deadzone for the left analog stick x axis
extern int32_t BEEFZONE_RX;         // outer deadzone for the left analog stick x axis

extern int32_t DEADZONE_BRAKE;      // inner deadzone for the analog brake (L2)
extern int32_t BEEFZONE_BRAKE;      // outer deadzone for the analog brake (L2)
extern int32_t DEADZONE_THROTTLE;   // inner deadzone for the analog throttle (R2)
extern int32_t BEEFZONE_THROTTLE;   // outer deadzone for the analog throttle (R2)


//-------------------------------------------
// Status LED
//-------------------------------------------

#define STATUS_LED_ENABLE
#define STATUS_LED_PIN              5
// #define STATUS_LED_POWER_PIN        8        // please make sure this doesn't conflict with anything else because it will be pulled high for the duration of the program
#define STATUS_NUM_LEDS             1
#define STATUS_LED_TYPE             NEOPIXEL
#define STATUS_LED_INIT_BRIGHTNESS  35