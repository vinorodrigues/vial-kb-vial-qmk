// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

uint8_t roll_dice(void);

void matrix_scan_dice(void);
void housekeeping_task_dice(void);

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_dice(void);
bool led_update_dice(led_t led_state);
#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_dice(void);

bool dice_process_toggle_keycode(keyrecord_t *record);
