// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "dice.h"

// needed for rand()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool dice_init = false;
bool dice_rolling_on = false;

#ifdef RGB_MATRIX_ENABLE

    #if !defined(DICE_1_LED_INDEX) || \
        !defined(DICE_2_LED_INDEX) || \
        !defined(DICE_3_LED_INDEX) || \
        !defined(DICE_4_LED_INDEX) || \
        !defined(DICE_5_LED_INDEX) || \
        !defined(DICE_6_LED_INDEX)
        #error "DICE_x_LED_INDEX (x = 1..6) must be defined in keymap config.h file"
    #endif

    #ifndef LED_COLOR_DICE
        #define LED_COLOR_DICE RGB_WHITE
    #endif

#endif  // RGB_MATRIX_ENABLE

uint8_t roll_dice(void) {
    if (!dice_init) {
        // code to seed the random generator at a random time
        // after powerup, ensuring unpredicatable randomness
        dice_init = true;
        srand(timer_read());
    }
    return (rand() % 6) + 1;
}

void housekeeping_task_dice(void) {
    // todo: ...
}

#ifdef RGB_MATRIX_ENABLE

void rgb_matrix_indicators_dice(void) {
    // todo: ...
}

bool led_update_dice(led_t led_state) {
    // todo: ...
    return true;
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_dice(void) {
    dice_init = false;
    dice_rolling_on = false;
}

void matrix_scan_dice(void) {
    // todo: ,,,
}

bool dice_process_toggle_keycode(keyrecord_t *record) {
    // todo: ...
    if (record->event.pressed) {
        // key down
        dice_rolling_on = true;
    } else {
        // key up
        dice_rolling_on = false;
        uint8_t r = roll_dice();
        char buff[2];  // 2, one for the character, one for the #0 string term.
        SEND_STRING( itoa(r, buff, 10) );
    }
    return false;
}
