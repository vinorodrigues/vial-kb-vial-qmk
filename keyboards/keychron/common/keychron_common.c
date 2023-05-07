// Copyright 2022 Keychron (https://www.keychron.com)
// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keychron_common.h"

// bool     is_siri_active = false;
// uint32_t siri_timer     = 0;
// // clang-format off
// key_combination_t key_comb_list[4] = {
//     {2, {KC_LWIN, KC_TAB}},
//     {2, {KC_LWIN, KC_E}},
//     {3, {KC_LSFT, KC_LCMD, KC_4}},
//     {2, {KC_LWIN, KC_C}}
// };

// static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};
// // clang-format on

void housekeeping_task_keychron(void) {
    // if (is_siri_active) {
    //     if (sync_timer_elapsed32(siri_timer) >= 500) {
    //         unregister_code(KC_LCMD);
    //         unregister_code(KC_SPACE);
    //         is_siri_active = false;
    //     }
    // }
}

#ifdef VIAL_ENABLE
static bool keychron_host_consumer_send(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        host_consumer_send(data);
    } else {
        host_consumer_send(0);
    }
    return false;  // Skip all further processing of this key
}
#endif  // VIAL_ENABLE

static bool keychron_register_code(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        register_code(data);
    } else {
        unregister_code(data);
    }
    return false;  // Skip all further processing of this key
}

static bool keychron_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
    } else {
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

static bool keychron_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3) {
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

bool process_record_keychron(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // macOS
        #ifdef VIAL_ENABLE
        case KC_MISSION_CONTROL: return keychron_host_consumer_send(record, _AC_SHOW_ALL_WINDOWS);  break;
        case KC_LAUNCHPAD: return keychron_host_consumer_send(record, _AC_SHOW_ALL_APPS);  break;
        #else
        case QK_KB_0: return keychron_register_code(record, KC_MISSION_CONTROL); break;
        case QK_KB_1: return keychron_register_code(record, KC_LAUNCHPAD); break;
        #endif  // VIAL_ENABLE

        case KC_LOPTN: return keychron_register_code(record, KC_LOPT); break;
        case KC_ROPTN: return keychron_register_code(record, KC_ROPT); break;
        case KC_LCMMD: return keychron_register_code(record, KC_LCMD); break;
        case KC_RCMMD: return keychron_register_code(record, KC_RCMD); break;
        case KC_SIRI: return keychron_register_code_2(record, KC_LOPT, KC_SPACE); break;
        case KC_SCREEN_SHOT: return keychron_register_code_3(record, KC_LSFT, KC_LCMD, KC_4); break;

        // Windows
        case KC_TASK_VIEW: return keychron_register_code_2(record, KC_LWIN, KC_TAB); break;
        case KC_FILE_EXPLORER: return keychron_register_code_2(record, KC_LWIN, KC_E); break;
        case KC_CORTANA: return keychron_register_code_2(record, KC_LWIN, KC_C); break;

        default: break;
    }
    
    return true;  // Process all other keycodes normally
}

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX)) || defined(SCROLL_LOCK_LED_INDEX)

#    define CAPS_NUM_LOCK_MAX_BRIGHTNESS 0xFF
#    ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        undef CAPS_NUM_LOCK_MAX_BRIGHTNESS
#        define CAPS_NUM_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    endif

#    define CAPS_NUM_LOCK_VAL_STEP 8
#    ifdef RGB_MATRIX_VAL_STEP
#        undef CAPS_NUM_LOCK_VAL_STEP
#        define CAPS_NUM_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
#    endif

extern void rgb_matrix_update_pwm_buffers(void);

uint8_t light_brightness_get(void) {
    uint8_t value = rgb_matrix_get_val();
    if (value < CAPS_NUM_LOCK_VAL_STEP) {
        value = CAPS_NUM_LOCK_VAL_STEP;
    } else if (value < (CAPS_NUM_LOCK_MAX_BRIGHTNESS - CAPS_NUM_LOCK_VAL_STEP)) {
        value += CAPS_NUM_LOCK_VAL_STEP; // one step more than current brightness
    } else {
        value = CAPS_NUM_LOCK_MAX_BRIGHTNESS;
    }
    return value;
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
#    if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        uint8_t v = light_brightness_get();
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v); // white, with the adjusted brightness
    }
#    endif
#    if defined(NUM_LOCK_LED_INDEX)
    if (host_keyboard_led_state().num_lock) {
        uint8_t v = light_brightness_get();
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v); // white, with the adjusted brightness
    }
#    endif
#    if defined(SCROLL_LOCK_LED_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        uint8_t v = light_brightness_get();
        rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, v, v, v); // white, with the adjusted brightness
    }
#    endif
    return true;
}

void rgb_matrix_indicators_none_kb(void) {
    rgb_matrix_indicators_kb();
    rgb_matrix_update_pwm_buffers();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if (rgb_matrix_is_enabled()
#    if defined(ENABLE_RGB_MATRIX_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_RAINDROPS)
#    endif
#    if defined(ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS)
        && (rgb_matrix_get_mode() != RGB_MATRIX_JELLYBEAN_RAINDROPS)
#    endif
#    if defined(ENABLE_RGB_MATRIX_PIXEL_RAIN)
        && (rgb_matrix_get_mode() != RGB_MATRIX_PIXEL_RAIN)
#    endif
    ) {
        return res;
    }

    if (res) {
#    if defined(CAPS_LOCK_LED_INDEX)
        if (led_state.caps_lock) {
            uint8_t v = light_brightness_get();
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v);
        } else {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
#    endif
#    if defined(NUM_LOCK_LED_INDEX)
        if (led_state.num_lock) {
            uint8_t v = light_brightness_get();
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v);
        } else {
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
#    endif
#    if defined(SCROLL_LOCK_LED_INDEX)
        if (led_state.scroll_lock) {
            uint8_t v = light_brightness_get();
            rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, v, v, v);
        } else {
            rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, 0, 0, 0);
        }
#    endif

        rgb_matrix_update_pwm_buffers();
    }
    return res;
}

#endif

#if defined(ENCODER_INTERRUPT_PATCH) && defined(ENCODER_ENABLE) && defined(PAL_USE_CALLBACKS)

static void encoder_pad_cb(void *param) {
    encoder_interrupt_read((uint32_t)param & 0XFF);
}

__attribute__((weak)) void keyboard_post_init_kb(void) {
    pin_t encoders_pad_a[NUM_ENCODERS] = ENCODERS_PAD_A;
    pin_t encoders_pad_b[NUM_ENCODERS] = ENCODERS_PAD_B;
    for (uint32_t i = 0; i < NUM_ENCODERS; i++) {
        palEnableLineEvent(encoders_pad_a[i], PAL_EVENT_MODE_BOTH_EDGES);
        palEnableLineEvent(encoders_pad_b[i], PAL_EVENT_MODE_BOTH_EDGES);
        palSetLineCallback(encoders_pad_a[i], encoder_pad_cb, (void *)i);
        palSetLineCallback(encoders_pad_b[i], encoder_pad_cb, (void *)i);
    }
}

#endif  // ENCODER_ENABLE

#ifdef LED_MATRIX_ENABLE

__attribute__((weak)) bool led_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max) {
    return true;
}

bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!led_matrix_indicators_advanced_ft(led_min, led_max)) { return false; }
    if (!led_matrix_indicators_advanced_user(led_min, led_max)) { return false; }
    return true;
}

#endif  // LED_MATRIX_ENABLE

#ifdef RGB_MATRIX_ENABLE

__attribute__((weak)) bool rgb_matrix_indicators_advanced_ft(uint8_t led_min, uint8_t led_max) {
    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_ft(led_min, led_max)) { return false; }
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) { return false; }
    return true;
}

#endif  // RGB_MATRIX_ENABLE
