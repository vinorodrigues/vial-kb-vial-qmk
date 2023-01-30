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

__attribute__((weak)) void rgb_matrix_indicators_keychron(void) {}
__attribute__((weak)) bool led_update_keychron(led_t led_state) { return true; }

void rgb_matrix_indicators_kb(void) {
    rgb_matrix_indicators_keychron();
}

bool led_update_kb(led_t led_state) {
    return led_update_keychron(led_state);
}

#endif // CAPS_LOCK_LED_INDEX
