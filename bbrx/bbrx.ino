// #include <cstdint>
#include <Arduino.h>
#include "controllers.h"
#include "event_manager.h"
#include "log.h"
#include "config.h"

#define LOG_TAG "main"

void setup() {

    // setup serial
    Serial.begin(115200);
    delay(1500);
    logi(LOG_TAG, "\n=== bbrx! ===");
    logi(LOG_TAG, "version:     %s", VERSION_STRING);
    logi(LOG_TAG, "build time:  %s %s", __DATE__, __TIME__);
    #ifdef GIT_HASH
        logi(LOG_TAG, "commit:      %s", GIT_HASH);
    #endif
    logi(LOG_TAG, "");

    // load config before SD
    // ideally this should be one of the first init actions
    load_config();

    // setup controller library
    controller_setup();

    // setup event manager and hardware needed by actions
    event_manager_setup();


    // main motor control bindings
    for (auto b : bindings) {
        initialise_binding(b);
    }
}

void loop() {

    // parse controller input and perform bound actions
    event_manager_update();

}
