// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "vinorodrigues_common.h"
#include "version.h"

bool macos_lock_enabled = false;
uint32_t timer_macos_lock_buffer = 0;

#ifndef MACOS_LOCK_DELAY
    #define MACOS_LOCK_DELAY (TAPPING_TERM + 1250)
#endif  // MACOS_LOCK_DELAY

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

void __do_lock_and_sleep(void) {
    send_string(SS_LCTL(SS_LGUI("q")) SS_DELAY(225) SS_TAP(X_ESC));
}

void housekeeping_task_vinorodrigues(void) {
    if (macos_lock_enabled && (sync_timer_elapsed32(timer_macos_lock_buffer) > MACOS_LOCK_DELAY)) {
        macos_lock_enabled = false;
        __do_lock_and_sleep();
    }
}

static bool __lock_and_sleep(keyrecord_t *record) {
    if ((get_mods() & MOD_MASK_CSAG)) {
        if (record->event.pressed) {
            __do_lock_and_sleep();
        }
    } else {
        if (record->event.pressed) {
            timer_macos_lock_buffer = sync_timer_read32();
            macos_lock_enabled = true;
        } else {
            macos_lock_enabled = false;
            timer_macos_lock_buffer = 0;  // arb cleanup
        }
    }
    return false;
}

static bool __eeprom_clear(keyrecord_t *record) {
    if (record->event.pressed) {
        rgb_matrix_set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0);  // All yellow
        rgb_matrix_update_pwm_buffers();
        wait_ms(10);  // give it time

        layer_state_t default_layer_tmp = default_layer_state;
        eeconfig_init_quantum();
        soft_reset_keyboard();
        default_layer_set(default_layer_tmp);

        wait_ms(10);  // give it time
    }
    return false;
}

static bool __keyboard_boot(keyrecord_t *record) {
    // does not really boot - just set's up the LED to show red
    if (record->event.pressed) {
        rgb_matrix_set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0, 0);  // All red
        rgb_matrix_update_pwm_buffers();
        wait_ms(10);  // give it time to change LED's
    }
    return true;  // NB! always TRUE = allow QMK to do it's thing
}

static bool __print_version(keyrecord_t *record) {
    if (!get_mods()) {
        if (!record->event.pressed) {
            SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " (v" QMK_VERSION ") [E");
            #ifdef EXTERNAL_EEPROM_ENABLE
            SEND_STRING("EPROM");
            #else
            SEND_STRING("FL/WL");
            #endif
            SEND_STRING("]");
        }
    }
    return false;
}

bool process_record_vinorodrigues(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        #ifdef APPLE_FN_ENABLE
        case MAGIC_TOGGLE_NKRO:
        case KC_APPLE_FN_KEY:
            if (record->event.pressed) {
                register_code(KC_APPLE_FN);
            } else {
                unregister_code(KC_APPLE_FN);
            }
            return false;  // Skip all further processing of this key
        case MAGIC_HOST_NKRO:
        case MAGIC_UNHOST_NKRO: return false;  // discard these keys
        #endif  // APPLE_FN_ENABLE

        case KC_LOCK_AND_SLEEP: return __lock_and_sleep(record);
        case KC_CLEAR_EEPROM: return __eeprom_clear(record);
        case QK_BOOT: return __keyboard_boot(record);
        case KC_VERSION: return __print_version(record);

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
