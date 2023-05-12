// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "stdint.h"
#include "quantum_keycodes.h"
#include "action.h"

#ifndef VIA_ENABLE
    #define USER00 (SAFE_RANGE)
#endif

#ifdef VIAL_ENABLE
    #define QK_KB_0 (USER00)
#endif

enum idobao_custom_keycodes {
    // Windows
    KC_TASK_VIEW = QK_KB_0,
    KC_FILE_EXPLORER,
    KC_CORTANA,

    // macOS
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD,
    KC_SIRI,
    KC_SCREEN_SHOT,
    KC_LOCK_AND_SLEEP,

    // General
    KC_CLEAR_EEPROM,
    KC_VERSION
};

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to Q1_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to Q1_LPAD
};

#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_CRTA KC_CORTANA

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_SNAP KC_SCREEN_SHOT
#define KC_LOCK KC_LOCK_AND_SLEEP

#define KC_EECL KC_CLEAR_EEPROM
#define KC_VERS KC_VERSION

void keyboard_pre_init_kb(void);

bool idobao_host_consumer_send(keyrecord_t *record, uint16_t data);
bool idobao_register_code(keyrecord_t *record, uint16_t data);
bool idobao_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2);
bool idobao_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3);

bool idobao_print_version(keyrecord_t *record);

void housekeeping_task_idobao(void);
bool process_record_idobao(uint16_t keycode, keyrecord_t *record);

#ifdef RGB_MATRIX_ENABLE
uint8_t light_brightness_get(void);
#endif  // RGB_MATRIX_ENABLE

// #if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX))

// bool rgb_matrix_indicators_idobao(void);
// void rgb_matrix_indicators_none_idobao(void);
// bool led_update_idobao(led_t led_state);

// #endif  // CAPS_LOCK_LED_INDEX | NUM_LOCK_LED_INDEX | SCROLL_LOCK_LED_INDEX
