// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "stdint.h"
#include "quantum_keycodes.h"
#include "action.h"

#ifndef VIA_ENABLE
    #define USER00 (SAFE_RANGE)
#endif

enum keycron_custom_keycodes {
    KC_MISSION_CONTROL = USER00,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_SIRI,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA
};

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to Q1_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to Q1_LPAD
};

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_SNAP KC_SCREEN_SHOT
#define KC_CRTN KC_CORTANA

void keyboard_pre_init_kb(void);

bool keychron_host_consumer_send(keyrecord_t *record, uint16_t data);
bool keychron_register_code(keyrecord_t *record, uint16_t data);
bool keychron_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2);
bool keychron_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3);

void housekeeping_task_keychron(void);
bool process_record_keychron(uint16_t keycode, keyrecord_t *record);

bool dip_switch_update_keychron(uint8_t index, bool active);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_keychron(uint8_t led_min, uint8_t led_max);
#endif  // RGB_MATRIX_ENABLE

#if defined(RGB_MATRIX_ENABLE) && ( defined(CAPS_LOCK_LED_INDEX) || \
    defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX) )
uint8_t light_brightness_get(void);
void rgb_matrix_indicators_keychron(void);
bool led_update_keychron(led_t led_state);
#endif  // RGB_MATRIX_ENABLE & CAPS_LOCK_LED_INDEX | NUM_LOCK_LED_INDEX | SCROLL_LOCK_LED_INDEX
