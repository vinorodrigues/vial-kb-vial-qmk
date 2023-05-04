// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "action.h"
#include "quantum_keycodes.h"

#ifdef VIAL_ENABLE
#define QK_KB_11 USER11
#endif

enum vinorodrigues_custom_codes {
    KC_APPLE_FN_KEY = QK_KB_11,
    KC_LOCK_AND_SLEEP,
    KC_CLEAR_EEPROM,
    KC_VERSION
};

#undef KC_APFN
#define KC_APFN KC_APPLE_FN_KEY
#define KC_LOCK KC_LOCK_AND_SLEEP
#define KC_EECL KC_CLEAR_EEPROM
#define KC_VRSN KC_VERSION

#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator
#define LED_FLAG_UNUSED    0xC0  // 0b11000000

void housekeeping_task_vinorodrigues(void);
bool process_record_vinorodrigues(uint16_t keycode, keyrecord_t *record);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_vinorodrigues(uint8_t led_min, uint8_t led_max);
#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_vinorodrigues(void);
