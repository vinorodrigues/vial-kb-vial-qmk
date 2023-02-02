// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keycode.h"
#include "quantum_keycodes.h"
#include "via.h"
#include "raw_hid.h"

#ifndef MAC_FN_LAYER
    #define MAC_FN_LAYER 1
#endif

#ifndef WIN_FN_LAYER
    #define WIN_FN_LAYER 3
#endif

// static void timer_3s_task(void);
// static void timer_300ms_task(void);

#define KEY_PRESS_FN (0x1<<0)
#define KEY_PRESS_J  (0x1<<1)
#define KEY_PRESS_Z  (0x1<<2)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z)

uint16_t key_press_status = 0;
uint32_t timer_3s_buffer = 0;
uint32_t timer_300ms_buffer = 0;
uint8_t factory_reset_count = 0;

static void timer_3s_task(void) {
    if (sync_timer_elapsed32(timer_3s_buffer) > 3000) {
        timer_3s_buffer = 0;
        if (key_press_status == KEY_PRESS_FACTORY_RESET) {
            timer_300ms_buffer = sync_timer_read32();
            factory_reset_count++;
            layer_state_t default_layer_tmp = default_layer_state;
            eeconfig_init_quantum();
            soft_reset_keyboard();
            default_layer_set(default_layer_tmp);
        }
        key_press_status = 0;
    }
}

static void timer_300ms_task(void) {
    if (timer_300ms_buffer && sync_timer_elapsed32(timer_300ms_buffer) > 300) {
        if (factory_reset_count++ > 6) {
            timer_300ms_buffer = 0;
            factory_reset_count = 0;
        } else {
            timer_300ms_buffer = sync_timer_read32();
        }
    }
}

static bool factory_rt(keyrecord_t *record, uint8_t data) {
    if (record->event.pressed) {
        key_press_status |= data;
        if ((key_press_status == KEY_PRESS_FACTORY_RESET) && (KEY_PRESS_FN != data)) {
            timer_3s_buffer = sync_timer_read32() | 1;
        }
    } else {
        key_press_status &= ~data;
        timer_3s_buffer = 0;
    }
    return true;
}

bool process_record_ft(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(MAC_FN_LAYER):
        case MO(WIN_FN_LAYER): return factory_rt(record, KEY_PRESS_FN);
        case KC_J: return factory_rt(record, KEY_PRESS_J);
        case KC_Z: return factory_rt(record, KEY_PRESS_Z);
        default:
            return true;   // Process all other keycodes normally
    }
}

void housekeeping_task_ft(void) {
    if (timer_3s_buffer) { timer_3s_task(); }
    if (timer_300ms_buffer) { timer_300ms_task(); }
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max) {
    if (timer_3s_buffer) {
        uint32_t elapsed = sync_timer_elapsed32(timer_3s_buffer);
        if ((elapsed >= 1000) && (elapsed < 2000)) {
            for (uint8_t i = led_min; i <= led_max; i++)
                rgb_matrix_set_color(i, RGB_YELLOW);
        } else if ((elapsed >= 2000) && (elapsed < 2900)) {
            for (uint8_t i = led_min; i <= led_max; i++)
                rgb_matrix_set_color(i, RGB_RED);
        } else if (elapsed >= 2900) {
            for (uint8_t i = led_min; i <= led_max; i++)
                rgb_matrix_set_color(i, HSV_OFF);
        }
    }
    return true;
}
#endif  // RGB_MATRIX_ENABLE
