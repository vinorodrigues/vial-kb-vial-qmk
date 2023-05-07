// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "idobao_common.h"

#ifdef VIAL_ENABLE
    #define QK_KB_0 (USER00)
#endif

#ifdef KC_VERSION
    #define __KC_LAST_USABLE (KC_VERSION + 1)
#else
    #define __KC_LAST_USABLE (QK_KB_0 + 10)
#endif

enum id27_custom_keycodes {
    KC_NUM_LOCK_LED = __KC_LAST_USABLE,
    RGB_TOGGLE_PER_KEY,
    RGB_TOGGLE_UNDERGLOW
};

#define KC_NLED KC_NUM_LOCK_LED
#define RGB_TPK RGB_TOGGLE_PER_KEY
#define RGB_TUG RGB_TOGGLE_UNDERGLOW

void keyboard_post_init_id27(void);
void eeconfig_init_id27(void);
// bool rgb_matrix_indicators_id27(void);
bool rgb_matrix_indicators_advanced_id27(uint8_t led_min, uint8_t led_max);

bool process_record_id27(uint16_t keycode, keyrecord_t *record);
