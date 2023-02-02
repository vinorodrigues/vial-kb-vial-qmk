// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "dice.h"

// needed for rand()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool dice_init = false;
uint8_t dice_last = 0;

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

    #ifndef DICE_ANIM_DELAY
        #define DICE_ANIM_DELAY 50  // 1/20th sec
    #endif

    #ifndef DICE_SHOW_DELAY
        #define DICE_SHOW_DELAY 2500  // 2.5 sec
    #endif

bool dice_rolling_on = false;
bool dice_showing_on = false;
uint32_t timer_dice_buffer = 0;

static int led_indices[6] = { \
    DICE_1_LED_INDEX, DICE_2_LED_INDEX, DICE_3_LED_INDEX, \
    DICE_4_LED_INDEX, DICE_5_LED_INDEX, DICE_6_LED_INDEX};

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
    #ifdef RGB_MATRIX_ENABLE
    if ((dice_rolling_on || dice_showing_on) && !rgb_matrix_is_enabled()) {
        dice_rolling_on = false;
        dice_showing_on = false;
        dice_last = 0;
        rgb_matrix_set_color(CAFFEINE_LED_INDEX, RGB_OFF);
    }
    #endif  // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_ENABLE

static void __dice_blink(void) {
    if ((dice_rolling_on || dice_showing_on) && (dice_last > 0)) {
        rgb_matrix_set_color(led_indices[dice_last - 1], LED_COLOR_DICE);
    }
}

void rgb_matrix_indicators_dice(void) {
    __dice_blink();
}

bool led_update_dice(led_t led_state) {
    __dice_blink();
    return true;
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_dice(void) {
    dice_init = false;
    #ifdef RGB_MATRIX_ENABLE
    dice_rolling_on = false;
    dice_showing_on = false;
    #endif  // RGB_MATRIX_ENABLE
    dice_last = 0;
}

void matrix_scan_dice(void) {
    #ifdef RGB_MATRIX_ENABLE

    if (dice_rolling_on && rgb_matrix_is_enabled()) {
        if ( (sync_timer_elapsed32(timer_dice_buffer) > DICE_ANIM_DELAY) ||
            (0 == dice_last) ) {
            timer_dice_buffer = sync_timer_read32();  // reset timer
            dice_last = roll_dice();
        }
    }

    if (dice_showing_on) {
        if (sync_timer_elapsed32(timer_dice_buffer) > DICE_SHOW_DELAY) {
            dice_showing_on = false;
            dice_last = 0;
        }
    }

    #endif  // RGB_MATRIX_ENABLE
}

bool dice_process_toggle_keycode(keyrecord_t *record) {
    // todo: ...
    if (record->event.pressed) {
        // key down
        #ifdef RGB_MATRIX_ENABLE
        dice_rolling_on = true;
        dice_showing_on = false;
        #endif  // RGB_MATRIX_ENABLE
    } else {
        // key up
        #ifdef RGB_MATRIX_ENABLE
        dice_rolling_on = false;
        #endif  // RGB_MATRIX_ENABLE

        dice_last = roll_dice();

        char buff[2];  // 2, one for the character, one for the #0 string term.
        SEND_STRING( itoa(dice_last, buff, 10) );

        #ifdef RGB_MATRIX_ENABLE
        dice_showing_on = true;
        timer_dice_buffer = sync_timer_read32();  // reset timer
        #endif  // RGB_MATRIX_ENABLE
    }
    return false;
}
