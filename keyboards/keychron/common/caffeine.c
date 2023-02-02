// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "caffeine.h"

bool caffeine_on = false;             // No Screen Saver
uint32_t timer_caffeine_buffer = 0;   // No Screen Saver timer buffer

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

void housekeeping_task_caffeine(void) {
    // swithc off blinking if RGB has been toggled off
    if (blink_on && !rgb_matrix_is_enabled()) {
        blink_on = false;
        rgb_matrix_set_color(CAFFEINE_LED_INDEX, RGB_OFF);
    }
}

#ifdef RGB_MATRIX_ENABLE

static void __caffeine_blink(void) {
    if (caffeine_on && rgb_matrix_is_enabled()) {
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
    caffeine_on = false;
    timer_caffeine_buffer = 0;
    #ifdef RGB_MATRIX_ENABLE
    blink_on = false;
    timer_blink_buffer = 0;
    #endif  // RGB_MATRIX_ENABLE
}

void matrix_scan_caffeine(void) {
    if (caffeine_on) {
        if (sync_timer_elapsed32(timer_caffeine_buffer) > CAFFEINE_KEY_DELAY) {  // 59 sec
            timer_caffeine_buffer = sync_timer_read32();  // reset timer
            tap_code(CAFFEINE_KEY_CODE);
            tap_code(KC_MS_RIGHT);
            tap_code(KC_MS_LEFT);
        }
    }
}

bool caffeine_process_toggle_keycode(keyrecord_t *record) {
    if (record->event.pressed) {
        caffeine_on = !caffeine_on;
        if (caffeine_on) {
            tap_code(CAFFEINE_KEY_CODE);
            timer_caffeine_buffer = sync_timer_read32();
        } else {
            #ifdef RGB_MATRIX_ENABLE
            blink_on = false;
            #endif  // RGB_MATRIX_ENABLE
        }
    }
    return false;
}
