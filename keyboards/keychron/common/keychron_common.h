// Copyright 2022 Keychron (https://www.keychron.com)
// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "stdint.h"
#ifdef VIA_ENABLE
#    include "via.h"
#endif

#ifdef VIAL_ENABLE
enum {
    QK_KB_0 = USER00,
    QK_KB_1,
    QK_KB_2,
    QK_KB_3,
    QK_KB_4,
    QK_KB_5,
    QK_KB_6,
    QK_KB_7,
    QK_KB_8,
    QK_KB_9,
    QK_KB_10,
    QK_KB_11,
    QK_KB_12,
    QK_KB_13,
    QK_KB_14,
    QK_KB_15
};
#endif  // VIAL_ENABLE

enum custom_keycodes {
    #ifdef VIAL_ENABLE
    KC_MISSION_CONTROL = QK_KB_0,
    KC_LAUNCHPAD,
    #endif  // VIAL_ENABLE
    KC_LOPTN = QK_KB_2,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_SIRI,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA
};

#ifdef VIAL_ENABLE
#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#endif  // VIAL_ENABLE
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_SNAP KC_SCREEN_SHOT
#define KC_CRTA KC_CORTANA

// typedef struct PACKED {
//     uint8_t len;
//     uint8_t keycode[3];
// } key_combination_t;

#ifdef VIAL_ENABLE
enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to Q1_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to Q1_LPAD
};
#endif  // VIAL_ENABLE

uint8_t light_brightness_get(void);

void housekeeping_task_keychron(void);
bool process_record_keychron(uint16_t keycode, keyrecord_t *record);
void keyboard_post_init_keychron(void);

#ifdef LED_MATRIX_ENABLE
bool led_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max);
bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
#endif

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
#endif
