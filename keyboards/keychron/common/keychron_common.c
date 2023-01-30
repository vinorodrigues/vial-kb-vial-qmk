// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#ifdef FACTORY_RESET_ENABLE
    #include "keychron_factory_test_common.h"
#endif  // FACTORY_RESET_ENABLE
#include "host.h"
#include "color.h"


#ifdef CAPS_LOCK_LED_COLOR
RGB caps_lock_led_color;
#endif  // CAPS_LOCK_LED_COLOR

#ifdef NUM_LOCK_LED_COLOR
RGB num_lock_led_color;
#endif  // NUM_LOCK_LED_COLOR

#ifdef SCROLL_LOCK_LED_COLOR
RGB scroll_lock_led_color;
#endif  // SCROLL_LOCK_LED_COLOR


#if defined(CAPS_LOCK_LED_COLOR) || defined(NUM_LOCK_LED_COLOR) || defined(SCROLL_LOCK_LED_COLOR) || defined(RGB2HSV_ENABLE)

static RGB __rgb(uint8_t r, uint8_t g, uint8_t b) {
    RGB rgb;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return rgb;
}

static HSV __hsv(uint8_t h, uint8_t s, uint8_t v) {
    HSV hsv;
    hsv.h = h;
    hsv.s = s;
    hsv.v = v;
    return hsv;
}

static HSV rgb_to_hsv(RGB rgb) {
    HSV hsv;
    uint8_t rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0) {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * (rgbMax - rgbMin) / hsv.v;
    if (hsv.s == 0) {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();

    #ifdef CAPS_LOCK_LED_INDEX
    #ifdef CAPS_LOCK_LED_COLOR
    caps_lock_led_color = __rgb(CAPS_LOCK_LED_COLOR);
    #else
    caps_lock_led_color = __rgb(RGB_WHITE);
    #endif  // CAPS_LOCK_LED_COLOR
    #endif  // CAPS_LOCK_LED_INDEX

    #ifdef NUM_LOCK_LED_INDEX
    #ifdef NUM_LOCK_LED_COLOR
    num_lock_led_color = __rgb(NUM_LOCK_LED_COLOR);
    #else
    num_lock_led_color = __rgb(RGB_WHITE);
    #endif  // NUM_LOCK_LED_COLOR
    #endif  // NUM_LOCK_LED_INDEX

    #ifdef SCROLL_LOCK_LED_INDEX
    #ifdef SCROLL_LOCK_LED_COLOR
    scroll_lock_led_color = __rgb(SCROLL_LOCK_LED_COLOR);
    #else
    scroll_lock_led_color = __rgb(RGB_WHITE);
    #endif  // SCROLL_LOCK_LED_COLOR
    #endif  // SCROLL_LOCK_LED_INDEX
}

#endif  // CAPS_LOCK_LED_COLOR | NUM_LOCK_LED_COLOR | SCROLL_LOCK_LED_COLOR


bool keychron_host_consumer_send(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        host_consumer_send(data);
    } else {
        host_consumer_send(0);
    }
    return false;  // Skip all further processing of this key
}

bool keychron_register_code(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        register_code(data);
    } else {
        unregister_code(data);
    }
    return false;  // Skip all further processing of this key
}

bool keychron_register_code_2(keyrecord_t *record, uint16_t data1, uint16_t data2) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
    } else {
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

bool keychron_register_code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3) {
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

void housekeeping_task_keychron(void) {
    #ifdef FACTORY_RESET_ENABLE
    housekeeping_task_ft();
    #endif
}

bool process_record_keychron(uint16_t keycode, keyrecord_t *record) {
    #ifdef FACTORY_RESET_ENABLE
    if (!process_record_ft(keycode, record)) {
        return false;
    }
    #endif

    switch (keycode) {
        // macOS
        case KC_MISSION_CONTROL: return keychron_host_consumer_send(record, _AC_SHOW_ALL_WINDOWS);
        case KC_LAUNCHPAD: return keychron_host_consumer_send(record, _AC_SHOW_ALL_APPS);
        case KC_LOPTN: return keychron_register_code(record, KC_LOPT);
        case KC_ROPTN: return keychron_register_code(record, KC_ROPT);
        case KC_LCMMD: return keychron_register_code(record, KC_LCMD);
        case KC_RCMMD: return keychron_register_code(record, KC_RCMD);
        case KC_SIRI: return keychron_register_code_2(record, KC_LOPT, KC_SPACE);
        case KC_SCREEN_SHOT: return keychron_register_code_3(record, KC_LSFT, KC_LCMD, KC_4);

        // Windows
        case KC_TASK_VIEW: return keychron_register_code_2(record, KC_LWIN, KC_TAB);
        case KC_FILE_EXPLORER: return keychron_register_code_2(record, KC_LWIN, KC_E);
        case KC_CORTANA: return keychron_register_code_2(record, KC_LWIN, KC_C);

        default:
            return true;  // Process all other keycodes normally
    }
}

__attribute__((weak)) bool dip_switch_update_keychron(uint8_t index, bool active) { return true; }

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_keychron(uint8_t led_min, uint8_t led_max) {
    #ifdef FACTORY_RESET_ENABLE
    if (!rgb_matrix_indicators_advanced_ft(led_min, led_max)) {
        return false;
    }
    #endif  // FACTORY_RESET_ENABLE
    return true;
}
#endif  // RGB_MATRIX_ENABLE

#if defined(RGB_MATRIX_ENABLE) && ( defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX) )

extern void rgb_matrix_update_pwm_buffers(void);

#ifndef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define INDICATOR_MAX_BRIGHTNESS 0xFF
#else
    #define INDICATOR_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#ifndef RGB_MATRIX_VAL_STEP
    #define INDICATOR_VAL_STEP 8
#else
    #define INDICATOR_VAL_STEP RGB_MATRIX_VAL_STEP
#endif

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

#if defined(CAPS_LOCK_LED_COLOR) || defined(NUM_LOCK_LED_COLOR) || defined(SCROLL_LOCK_LED_COLOR)
static void __rgb_matrix_set_color_b(int index, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t v = light_brightness_get();

    HSV hsv = rgb_to_hsv(__rgb(r, g, b));
    RGB rgb = hsv_to_rgb(__hsv(hsv.h, hsv.s, v));
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}
#else
static void __rgb_matrix_set_color_w(int index) {
    uint8_t v = light_brightness_get();
    rgb_matrix_set_color(index, v, v, v);
}
#endif  // CAPS_LOCK_LED_COLOR | NUM_LOCK_LED_COLOR | SCROLL_LOCK_LED_COLOR

void rgb_matrix_indicators_keychron(void) {
    // this code executes when the matrix is enabled

    #ifdef CAPS_LOCK_LED_INDEX
    if (host_keyboard_led_state().caps_lock) {
        #ifdef CAPS_LOCK_LED_COLOR
        __rgb_matrix_set_color_b(CAPS_LOCK_LED_INDEX, caps_lock_led_color.r, caps_lock_led_color.g, caps_lock_led_color.b);
        #else
        __rgb_matrix_set_color_w(CAPS_LOCK_LED_INDEX);
        #endif  // CAPS_LOCK_LED_COLOR
    }
    #endif  // CAPS_LOCK_LED_INDEX

    #ifdef NUM_LOCK_LED_INDEX
    if (host_keyboard_led_state().num_lock) {
        #ifdef NUM_LOCK_LED_COLOR
        __rgb_matrix_set_color_b(NUM_LOCK_LED_INDEX, num_lock_led_color.r, num_lock_led_color.g, num_lock_led_color.b);
        #else
        __rgb_matrix_set_color_w(NUM_LOCK_LED_INDEX);
        #endif  // NUM_LOCK_LED_COLOR
    }
    #endif  // NUM_LOCK_LED_INDEX

    #ifdef SCROLL_LOCK_LED_INDEX
    if (host_keyboard_led_state().scroll_lock) {
        #ifdef SCROLL_LOCK_LED_COLOR
        __rgb_matrix_set_color_b(SCROLL_LOCK_LED_INDEX, scroll_lock_led_color.r, scroll_lock_led_color.g, scroll_lock_led_color.b);
        #else
        __rgb_matrix_set_color_w(SCROLL_LOCK_LED_INDEX);
        #endif  // SCROLL_LOCK_LED_COLOR
    }
    #endif  // SCROLL_LOCK_LED_INDEX
}

bool led_update_keychron(led_t led_state) {
    // this code executes regardless of matrix enabled state
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

    // this code executes when the matrix is NOT enabled
    if (res) {
        #ifdef CAPS_LOCK_LED_INDEX
        if (led_state.caps_lock) {
            #ifdef CAPS_LOCK_LED_COLOR
            __rgb_matrix_set_color_b(CAPS_LOCK_LED_INDEX, caps_lock_led_color.r, caps_lock_led_color.g, caps_lock_led_color.b);
            #else
            __rgb_matrix_set_color_w(CAPS_LOCK_LED_INDEX);
            #endif  // CAPS_LOCK_LED_COLOR
        } else {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, HSV_OFF);
        }
        #endif  // CAPS_LOCK_LED_INDEX

        #ifdef NUM_LOCK_LED_INDEX
        if (led_state.num_lock) {
            #ifdef NUM_LOCK_LED_COLOR
            __rgb_matrix_set_color_b(NUM_LOCK_LED_INDEX, num_lock_led_color.r, num_lock_led_color.g, num_lock_led_color.b);
            #else
            __rgb_matrix_set_color_w(NUM_LOCK_LED_INDEX);
            #endif  // NUM_LOCK_LED_COLOR
        } else {
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, HSV_OFF);
        }
        #endif  // NUM_LOCK_LED_INDEX

        #ifdef SCROLL_LOCK_LED_INDEX
        if (led_state.scroll_lock) {
            #ifdef SCROLL_LOCK_LED_COLOR
            __rgb_matrix_set_color_b(SCROLL_LOCK_LED_INDEX, scroll_lock_led_color.r, scroll_lock_led_color.g, scroll_lock_led_color.b);
            #else
            __rgb_matrix_set_color_w(SCROLL_LOCK_LED_INDEX);
            #endif  // SCROLL_LOCK_LED_COLOR
        } else {
            rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, HSV_OFF);
        }
        #endif  // SCROLL_LOCK_LED_INDEX

        rgb_matrix_update_pwm_buffers();
    }

    return res;
}

#endif  // RGB_MATRIX_ENABLE & CAPS_LOCK_LED_INDEX | NUM_LOCK_LED_INDEX | SCROLL_LOCK_LED_INDEX
