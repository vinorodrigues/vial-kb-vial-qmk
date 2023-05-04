// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

const matrix_row_t matrix_mask[] = {
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111111111,
    0b1111111111101111,
};

#ifdef DIP_SWITCH_ENABLE

__attribute__((weak)) bool dip_switch_update_ft(uint8_t index, bool active) {
    return true;
}

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_ft(index, active)) { return false; }
    if (!dip_switch_update_user(index, active)) { return false; }

    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif
