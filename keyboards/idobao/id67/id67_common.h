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

#ifdef RGB_MATRIX_ENABLE

enum id67_custom_keycodes {
    KC_TOGGLE_CAPS_LOCK_LED = __KC_LAST_USABLE,
    RGB_TOGGLE_PER_KEY,
    RGB_TOGGLE_UNDERGLOW
};

#define KC_CLED KC_TOGGLE_CAPS_LOCK_LED
#define RGB_TPK RGB_TOGGLE_PER_KEY
#define RGB_TUG RGB_TOGGLE_UNDERGLOW

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_id67(void);
void eeconfig_init_id67(void);
// bool rgb_matrix_indicators_id67(void);
bool rgb_matrix_indicators_advanced_id67(uint8_t led_min, uint8_t led_max);

bool process_record_id67(uint16_t keycode, keyrecord_t *record);
