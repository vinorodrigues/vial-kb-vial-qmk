// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX))

// #    define CAPS_NUM_LOCK_MAX_BRIGHTNESS 0xFF
// #    ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
// #        undef CAPS_NUM_LOCK_MAX_BRIGHTNESS
// #        define CAPS_NUM_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
// #    endif

// #    define CAPS_NUM_LOCK_VAL_STEP 8
// #    ifdef RGB_MATRIX_VAL_STEP
// #        undef CAPS_NUM_LOCK_VAL_STEP
// #        define CAPS_NUM_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
// #    endif

// extern void rgb_matrix_update_pwm_buffers(void);

// static uint8_t light_brightness_get(void) {
//     uint8_t value = rgb_matrix_get_val();
//     if (value < CAPS_NUM_LOCK_VAL_STEP) {
//         value = CAPS_NUM_LOCK_VAL_STEP;
//     } else if (value < (CAPS_NUM_LOCK_MAX_BRIGHTNESS - CAPS_NUM_LOCK_VAL_STEP)) {
//         value += CAPS_NUM_LOCK_VAL_STEP; // one step more than current brightness
//     } else {
//         value = CAPS_NUM_LOCK_MAX_BRIGHTNESS;
//     }
//     return value;
// }

/* bool rgb_matrix_indicators_kb(void) {
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
    return true;
} */

/* void rgb_matrix_indicators_none_kb(void) {
    rgb_matrix_indicators_kb();
    rgb_matrix_update_pwm_buffers();
} */

/* bool led_update_kb(led_t led_state) {
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
        rgb_matrix_update_pwm_buffers();
    }
    return res;
} */

__attribute__((weak)) void rgb_matrix_indicators_keychron(void) {}
__attribute__((weak)) bool led_update_keychron(led_t led_state) { return true; }

void rgb_matrix_indicators_kb(void) {
    rgb_matrix_indicators_keychron();
}

bool led_update_kb(led_t led_state) {
    return led_update_keychron(led_state);
}

#endif // RGB_MATRIX_ENABLE
