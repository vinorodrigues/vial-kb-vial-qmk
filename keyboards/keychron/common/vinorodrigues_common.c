// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"
#include "keychron_common.h"
#include "vinorodrigues_common.h"

#ifdef RGB_MATRIX_ENABLE

typedef union {
    uint32_t raw;
    struct {
        bool lyr_led:1;
        bool caps_led:1;
        bool num_led:1;
        bool scrl_led:1;
    };
} led_sngltn_t;

led_sngltn_t led_sngltn;

extern void rgb_matrix_update_pwm_buffers(void);

#endif  // RGB_MATRIX_ENABLE

void housekeeping_task_vinorodrigues(void) { }

bool process_record_vinorodrigues(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case KC_CLEAR_EEPROM:
            if (record->event.pressed) {
                rgb_matrix_set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0);  // All yellow
                rgb_matrix_driver.flush();
                wait_ms(10);  // give it time

                layer_state_t default_layer_tmp = default_layer_state;
                eeconfig_init_quantum();
                soft_reset_keyboard();
                default_layer_set(default_layer_tmp);

                wait_ms(10);  // give it time

                return false;
            } else {
                return true;
            }

        case QK_BOOT:
            if (record->event.pressed) {
                rgb_matrix_set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0, 0);  // All red
                rgb_matrix_update_pwm_buffers();
                wait_ms(10);  // give it time to change LED's
            }
            return true;  // NB! always TRUE = allow QMK to do it's thing

        case KC_VERSION:
            if (!get_mods()) {
                if (!record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " (v" QMK_VERSION ") [E");
                    #ifdef EEPROM_ENABLE
                    SEND_STRING("EPROM");
                    #else
                    SEND_STRING("FL/WL");
                    #endif
                    SEND_STRING("]");
                }
            }
            return false;

        default:
            return true;
    }
}

#ifdef RGB_MATRIX_ENABLE

static void __rgb_matrix_set_all_color_by_flag(uint8_t led_min, uint8_t led_max, uint8_t flag, uint8_t R, uint8_t G, uint8_t B) {
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (0 != (g_led_config.flags[i] & flag)) {
            rgb_matrix_set_color(i, R, G, B);
        }
    }
}

bool rgb_matrix_indicators_advanced_vinorodrigues(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    #ifdef LED_COLOR_ALPHA_CAPS
    // caps-lock indicators
    if (host_keyboard_led_state().caps_lock) {
        __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_ALPHA_KEY, LED_COLOR_ALPHA_CAPS);
        led_sngltn.caps_led = true;
    } else if (led_sngltn.caps_led) {
        __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_ALPHA_KEY, HSV_OFF);
        led_sngltn.caps_led = false;
    }
    #endif  // LED_COLOR_ALPHA_CAPS

    // layer indicators
    switch (layer) {
        #ifdef LED_COLOR_LAYER_0
        case 0:
            __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_LAYER_IND, LED_COLOR_LAYER_0);
            led_sngltn.lyr_led = true;
            break;
        #endif  // LED_COLOR_LAYER_0

        #ifdef LED_COLOR_LAYER_1
        case 1:
            __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_LAYER_IND, LED_COLOR_LAYER_1);
            led_sngltn.lyr_led = true;
            break;
        #endif  // LED_COLOR_LAYER_1

        #ifdef LED_COLOR_LAYER_2
        case 2:
            __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_LAYER_IND, LED_COLOR_LAYER_2);
            led_sngltn.lyr_led = true;
            break;
        #endif  // LED_COLOR_LAYER_2

        #ifdef LED_COLOR_LAYER_3
        case 3:
            __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_LAYER_IND, LED_COLOR_LAYER_3);
            led_sngltn.lyr_led = true;
            break;
        #endif  // LED_COLOR_LAYER_3

        #ifdef LED_COLOR_LAYER_4
        case 4:
            __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_LAYER_IND, LED_COLOR_LAYER_4);
            led_sngltn.lyr_led = true;
            break;
        #endif  // LED_COLOR_LAYER_4

        default:
            if (led_sngltn.lyr_led) {
                __rgb_matrix_set_all_color_by_flag(led_min, led_max, LED_FLAG_LAYER_IND, HSV_OFF);
                led_sngltn.lyr_led = false;
            }
            break;  // do nothing
    }
    return true;
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_vinorodrigues(void) {
    #ifdef RGB_MATRIX_ENABLE
    led_sngltn.raw = 0;
    #endif  // RGB_MATRIX_ENABLE
}

// void eeconfig_init_vinorodrigues(void) {
//     // EEPROM is getting reset!
// }
