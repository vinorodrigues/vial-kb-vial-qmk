// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "stdint.h"

bool process_record_ft(uint16_t keycode, keyrecord_t *record);
void housekeeping_task_ft(void);

#ifdef LED_MATRIX_ENABLE
bool led_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max);
#endif // LED_MATRIX_ENABLE

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max);
#endif // RGB_MATRIX_ENABLE

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_ft(uint8_t index, bool active);
#endif // DIP_SWITCH_ENABLE
