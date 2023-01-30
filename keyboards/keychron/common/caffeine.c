// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "caffeine.h"

bool noss_on = false;             // No Screen Saver
uint32_t timer_noss_buffer = 0;   // No Screen Saver timer buffer

#ifdef RGB_MATRIX_ENABLE

bool blink_on = false;            // Blink LED timer buffer
uint32_t timer_blink_buffer = 0;  // Blink LED timer buffer

    #ifndef CAFFEINE_LED_INDEX
        #error "CAFFEINE_LED_INDEX should be defined"
    #endif  // CAFFEINE_LED_INDEX

    #ifndef LED_COLOR_CAFFEINE
        #error "LED_COLOR_CAFFEINE should be defined"
    #endif  // LED_COLOR_CAFFEINE

    #ifndef CAFFEINE_BLINK_DELAY
        #define CAFFEINE_BLINK_DELAY 1000
    #endif  // CAFFEINE_BLINK_DELAY

#endif  // RGB_MATRIX_ENABLE

#ifndef CAFFEINE_KEY_DELAY
    #define CAFFEINE_KEY_DELAY 59000
#endif  // CAFFEINE_KEY_DELAY

#ifndef CAFFEINE_KEY_CODE
    #define CAFFEINE_KEY_CODE KC_RIGHT_CTRL
#endif  // CAFFEINE_KEY_CODE


#ifdef RGB_MATRIX_ENABLE

static void __caffeine_blink(void) {
    if (noss_on) {
        if (sync_timer_elapsed32(timer_blink_buffer) > CAFFEINE_BLINK_DELAY) {  // every second
            timer_blink_buffer = sync_timer_read32();  // reset timer
            blink_on = !blink_on;
        }
    }

    if (blink_on) {
        // uint8_t v = light_brightness_get();
        rgb_matrix_set_color(CAFFEINE_LED_INDEX, LED_COLOR_CAFFEINE);
    }
}

void rgb_matrix_indicators_caffeine(void) {
    __caffeine_blink();
}

bool led_update_caffeine(led_t led_state) {
    __caffeine_blink();
    return true;
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_caffeine(void) {
    noss_on = false;
    blink_on = false;
    timer_noss_buffer = 0;
    timer_blink_buffer = 0;
}

void matrix_scan_caffeine(void) {
    if (noss_on) {
        if (sync_timer_elapsed32(timer_noss_buffer) > CAFFEINE_KEY_DELAY) {  // 59 sec
            timer_noss_buffer = sync_timer_read32();  // reset timer
            tap_code(CAFFEINE_KEY_CODE);
        }
    }
}

bool caffeine_process_toggle_keycode(keyrecord_t *record) {
    if (record->event.pressed) {
        noss_on = !noss_on;
        if (noss_on) {
            timer_noss_buffer = sync_timer_read32();
        } else {
            blink_on = false;
        }
    }
    return false;
}
