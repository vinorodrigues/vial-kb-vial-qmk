// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false;}
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

extern void rgb_matrix_update_pwm_buffers(void);

__attribute__((weak)) bool rgb_matrix_indicators_keychron(void) { return true; }
__attribute__((weak)) bool led_update_keychron(led_t led_state) { return true; }

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) return false;
    return rgb_matrix_indicators_keychron();
}

bool led_update_kb(led_t led_state) {
    if (!led_update_user(led_state)) return false;
    if (!led_update_keychron(led_state)) return false;
    rgb_matrix_update_pwm_buffers();
    return true;
}

#endif // RGB_MATRIX_ENABLE
