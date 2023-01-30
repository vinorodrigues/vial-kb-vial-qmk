// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "action.h"
#include "quantum_keycodes.h"
#include "keychron_common.h"

enum vinorodrigues_custom_codes {
    __DONT_USE_LAST_FROM_KC_CODES = KC_CORTANA,
    KC_NO_SCREEN_SAVER,
    KC_ROLL_DICE,
    KC_CLEAR_EEPROM,
    KC_VERSION
};

#define KC_NOSS KC_NO_SCREEN_SAVER
#define KC_DICE KC_ROLL_DICE
#define KC_EECL KC_CLEAR_EEPROM
#define KC_VRSN KC_VERSION

#define KC_CAFFEINE_TOGGLE KC_NO_SCREEN_SAVER  // for `caffeine.c`
#define KC_ROLL_THE_DICE KC_ROLL_DICE  // for `dice.c`

#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator
#define LED_FLAG_UNUSED    0xC0  // 0b11000000

void housekeeping_task_vinorodrigues(void);
bool process_record_vinorodrigues(uint16_t keycode, keyrecord_t *record);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_vinorodrigues(uint8_t led_min, uint8_t led_max);
#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_vinorodrigues(void);
void eeconfig_init_vinorodrigues(void);
