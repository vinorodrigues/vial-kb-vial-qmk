// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "idobao_common.h"

enum id61_custom_keycodes {
    KC_MISSION_CONTROL_2 = QK_KB_0,  // macOS Open Mission Control
    KC_LAUNCHPAD_2,                  // macOS Open Launchpad
    KC_TOGGLE_ARROW_MODE,            // toggle right modifiers are arrows feature
    KC_RSHIFT_OR_UP,                 // right shift or up arrow
    KC_RALT_OR_LEFT,                 // right alt or left arrow
    KC_APP_OR_DOWN,                  // menu or down arrow (Windows Menu)
    KC_RGUI_OR_LEFT,                 // right gui or left arrow (macOS Command)
    KC_RALT_OR_DOWN,                 // right alt or down arrow (macOS Option)
    KC_RCTL_OR_RIGHT,                // right ctrl ot right arrow
    KC_VERSION_2                     // debug, type version
};

#undef KC_MCTL
#define KC_MCTL KC_MISSION_CONTROL_2
#undef KC_LPAD
#define KC_LPAD KC_LAUNCHPAD_2
#define KC_ARRW KC_TOGGLE_ARROW_MODE
#define KC_S_UP KC_RSHIFT_OR_UP
#define KC_A_LF KC_RALT_OR_LEFT
#define KC_M_DN KC_APP_OR_DOWN
#define KC_G_LF KC_RGUI_OR_LEFT
#define KC_A_DN KC_RALT_OR_DOWN
#define KC_C_RT KC_RCTL_OR_RIGHT
#undef KB_VERS
#define KB_VERS KC_VERSION_2

void keyboard_post_init_id61(void);
void eeconfig_init_id61(void);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_id61(uint8_t led_min, uint8_t led_max);
#endif

bool process_record_id61(uint16_t keycode, keyrecord_t *record);
