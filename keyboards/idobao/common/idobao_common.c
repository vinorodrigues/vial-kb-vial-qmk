// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "idobao_common.h"
#include "version.h"

bool macos_lock_enabled = false;
uint32_t timer_macos_lock_buffer = 0;

#ifndef MACOS_LOCK_DELAY
    #define MACOS_LOCK_DELAY (TAPPING_TERM + 1250)
#endif  // MACOS_LOCK_DELAY

bool idobao_host_consumer_send(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        host_consumer_send(data);
    } else {
        host_consumer_send(0);
    }
    return false;  // Skip all further processing of this key
}

bool idobao_register_code(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        register_code(data);
    } else {
        unregister_code(data);
    }
    return false;  // Skip all further processing of this key
}

bool idobao_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
    } else {
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

bool idobao_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
        register_code(data3);
    } else {
        unregister_code(data3);
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

static bool __print_version(keyrecord_t *record) {
    if (!get_mods()) {
        if (!record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " (v" QMK_VERSION ")");
            }
        }
    return false;
}

static bool __eeprom_clear(keyrecord_t *record) {
    if (record->event.pressed) {
        eeconfig_init_quantum();
        soft_reset_keyboard();
        wait_ms(10);  // give it time
    }
    return false;
}

static bool __lock_and_sleep(keyrecord_t *record) {
    if ((get_mods() & MOD_MASK_CSAG)) {
        return idobao_register_code_2(record, KC_LGUI, KC_L);
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

void housekeeping_task_idobao(void) {
    if (macos_lock_enabled && (sync_timer_elapsed32(timer_macos_lock_buffer) > MACOS_LOCK_DELAY)) {
        macos_lock_enabled = false;
        SEND_STRING_DELAY( SS_LGUI("l"), 0 );
    }
}

bool process_record_idobao(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Windows
        case KC_TASK_VIEW:       return idobao_register_code_2(record, KC_LWIN, KC_TAB); break;
        case KC_FILE_EXPLORER:   return idobao_register_code_2(record, KC_LWIN, KC_E); break;
        case KC_CORTANA:         return idobao_register_code_2(record, KC_LWIN, KC_C); break;

        // macOS
        case KC_MISSION_CONTROL: return idobao_host_consumer_send(record, _AC_SHOW_ALL_WINDOWS); break;
        case KC_LAUNCHPAD:       return idobao_host_consumer_send(record, _AC_SHOW_ALL_APPS); break;
        case KC_SIRI:            return idobao_register_code_2(record, KC_LOPT, KC_SPACE); break;
        case KC_SCREEN_SHOT:     return idobao_register_code_3(record, KC_LSFT, KC_LCMD, KC_4); break;
        case KC_LOCK_AND_SLEEP:  return __lock_and_sleep(record); break;

        // general
        case KC_CLEAR_EEPROM:    return __eeprom_clear(record); break;
        case KC_VERSION:         return __print_version(record); break;

        default: break;
    }
    return true;  // Process all other keycodes normally
}

#ifdef RGB_MATRIX_ENABLE

#define INDICATOR_MAX_BRIGHTNESS 160
#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #undef INDICATOR_MAX_BRIGHTNESS
    #define INDICATOR_MAX_BRIGHTNESS (RGB_MATRIX_MAXIMUM_BRIGHTNESS)
#endif

#define INDICATOR_VAL_STEP 8
#ifdef RGB_MATRIX_VAL_STEP
    #undef INDICATOR_VAL_STEP
    #define INDICATOR_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

extern void rgb_matrix_update_pwm_buffers(void);

uint8_t light_brightness_get(void) {
    uint8_t value = rgb_matrix_get_val();
    if (value < INDICATOR_VAL_STEP) {
        value = INDICATOR_VAL_STEP;
    } else if (value < (INDICATOR_MAX_BRIGHTNESS - INDICATOR_VAL_STEP)) {
        value += INDICATOR_VAL_STEP; // one step more than current brightness
    } else {
        value = INDICATOR_MAX_BRIGHTNESS;
    }
    return value;
}

void shutdown_user(void) {
    uint8_t v = light_brightness_get();
    rgb_matrix_set_color_all(v, 0, 0);
    rgb_matrix_update_pwm_buffers();
}

#endif  // RGB_MATRIX_ENABLE

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX))

typedef union {
    uint8_t raw;
    struct {
        #ifdef CAPS_LOCK_LED_INDEX
        bool cl:1;
        #endif
        #ifdef NUM_LOCK_LED_INDEX
        bool nl:1;
        #endif
        #ifdef SCROLL_LOCK_LED_INDEX
        bool sl:1;
        #endif
    };
} led_on_t;

led_on_t led_on = {.raw = 0};

static void __set_indicators(led_t led_state) {
    uint8_t v = light_brightness_get();

    #if defined(CAPS_LOCK_LED_INDEX)
    if (led_state.caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v);
        led_on.cl = true;
    } else {
        if (led_on.cl) {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
            led_on.cl = false;
        }
    }
    #endif
    #if defined(NUM_LOCK_LED_INDEX)
    if (led_state.num_lock) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v);
        led_on.nl = true;
    } else {
        if (led_on.nl) {
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, 0, 0, 0);
            led_on.nl = false;
        }
    }
    #endif
    #if defined(SCROLL_LOCK_LED_INDEX)
    if (led_state.scroll_lock) {
        rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, v, v, v);
        led_on.sl = true;
    } else {
        if (led_on.sl) {
            rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, 0, 0, 0);
            led_on.sl = false;
        }
    }
    #endif
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { return false; }
    __set_indicators( host_keyboard_led_state() );
    return true;
}

void rgb_matrix_indicators_none_kb(void) {
    rgb_matrix_indicators_kb();
    rgb_matrix_update_pwm_buffers();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (rgb_matrix_is_enabled()
        #if defined(ENABLE_RGB_MATRIX_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_RAINDROPS)
        #endif
        #if defined(ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_JELLYBEAN_RAINDROPS)
        #endif
        #if defined(ENABLE_RGB_MATRIX_PIXEL_RAIN)
        && (rgb_matrix_get_mode() != RGB_MATRIX_PIXEL_RAIN)
        #endif
    ) {
        return res;
    }

    if (res) {
        __set_indicators( led_state );
        rgb_matrix_update_pwm_buffers();
    }
    return res;
}

#endif  // RGB_MATRIX_ENABLE & (CAPS_LOCK_LED_INDEX | NUM_LOCK_LED_INDEX | SCROLL_LOCK_LED_INDEX)
