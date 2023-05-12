// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "string.h"
#include "idobao_common.h"
#include "id67_common.h"

#ifdef RGB_MATRIX_ENABLE
#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator
#endif

typedef union {
    uint8_t raw;
    struct {
        bool rgb_disable_perkey:1;
        #ifndef ID67_DISABLE_UNDERGLOW
        bool rgb_disable_underglow:1;
        #endif  // ID67_DISABLE_UNDERGLOW
        bool rgb_disable_capslock:1;
    };
} user_config_t;

#ifdef RGB_MATRIX_ENABLE
const uint8_t g_led_config_new_flags[RGB_MATRIX_LED_COUNT] = {
    // Extended LED Index to Flag
    // ** Remember: on ID67 this is in reverse order
    0x21, 0x01, 0x01, 0x01, 0x01,                   0x04,             0x01,       0x01, 0x21,
    0x21, 0x01, 0x01, 0x04, 0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,       0x21,
    0x21, 0x01,       0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x29,
    0x21, 0x04, 0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x21,
    0x21, 0x01, 0x04, 0x04, 0x04, 0x04, 0x24, 0x24, 0x24, 0x24, 0x04, 0x04, 0x04, 0x04, 0x21
    #ifndef ID67_DISABLE_UNDERGLOW
    , 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02
    #endif
};
#endif

user_config_t user_config = {.raw = 0};
bool led_on_lyr = false;

#ifdef RGB_MATRIX_ENABLE

void keyboard_pre_init_kb(void) {
    // override `info.json` flags with new values
    memcpy(g_led_config.flags, g_led_config_new_flags, RGB_MATRIX_LED_COUNT);
}

static void id67_set_rgb_mode(void) {
    uint8_t flags = LED_FLAG_ALL;

    if (user_config.rgb_disable_perkey
        #ifndef ID67_DISABLE_UNDERGLOW
        && user_config.rgb_disable_underglow
        #endif  // ID67_DISABLE_UNDERGLOW
        ) {
        flags = 0;  // All OFF Condition
    } else {
        if (user_config.rgb_disable_perkey) {
            flags = LED_FLAG_UNDERGLOW | 0xF0;
        }
        #ifndef ID67_DISABLE_UNDERGLOW
        if (user_config.rgb_disable_underglow) {
            flags = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR | 0xF0;
        }
        #endif  // ID67_DISABLE_UNDERGLOW
    }

    if (flags == 0) {
        rgb_matrix_set_flags(0);
        rgb_matrix_set_color_all(HSV_OFF);
    } else {
        rgb_matrix_set_flags(flags);
        rgb_matrix_enable_noeeprom();
    }
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_id67(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    #ifdef RGB_MATRIX_ENABLE
    id67_set_rgb_mode();
    #endif  // RGB_MATRIX_ENABLE
}

void eeconfig_init_id67(void) {
    // EEPROM is getting reset!
    #ifdef RGB_MATRIX_ENABLE
    user_config.raw = 0;
    id67_set_rgb_mode();
    #endif  // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_advanced_id67(uint8_t led_min, uint8_t led_max) {
    uint8_t v = rgb_matrix_get_val();

    if ((v > 0) && (!user_config.rgb_disable_perkey) && (!user_config.rgb_disable_capslock) && host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if ((g_led_config.flags[i] & LED_FLAG_ALPHA_KEY) != 0)  {
                rgb_matrix_set_color(i, v, 0, 0);  // red
            }
        }
    }

    v = light_brightness_get();
    uint8_t current_layer = get_highest_layer(layer_state);
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    if (!user_config.rgb_disable_perkey) {

        switch (current_layer) {
            case 1: b = v; led_on_lyr = true; break;  // blue
            case 2: g = v; led_on_lyr = true; break;  // green
            case 3: r = v; led_on_lyr = true; break;  // red
            default: break;
        }
    }

    if (led_on_lyr) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if ((g_led_config.flags[i] & LED_FLAG_LAYER_IND) != 0) {
                rgb_matrix_set_color(i, r, g, b);
            }
        }
        led_on_lyr = false;
    }

    return true;
}

bool id67_toggle_rgb(keyrecord_t *record) {
    /* roll through the LED modes
     * |    Level   | Per-key | Underglow |
     * |------------|---------|-----------|
     * | 0 (defalt) |   on    |    on     |
     * |     1      |   OFF   |    on     |
     * |     2      |   on    |    OFF    |
     * |     3      |   OFF   |    OFF    |
     */
    if (record->event.pressed) {
        if ( (!user_config.rgb_disable_perkey)
            #ifndef ID67_DISABLE_UNDERGLOW
            && (!user_config.rgb_disable_underglow)
            #endif  // ID67_DISABLE_UNDERGLOW
            ) {
            user_config.rgb_disable_perkey = 1;
        #ifndef ID67_DISABLE_UNDERGLOW
        } else if ( user_config.rgb_disable_perkey && (!user_config.rgb_disable_underglow) ) {
            user_config.rgb_disable_perkey = 0;
            user_config.rgb_disable_underglow = 1;
        } else if ( (!user_config.rgb_disable_perkey) && user_config.rgb_disable_underglow ) {
            user_config.rgb_disable_perkey = 1;
        #endif  // ID67_DISABLE_UNDERGLOW
        } else {
            user_config.rgb_disable_perkey = 0;
            #ifndef ID67_DISABLE_UNDERGLOW
            user_config.rgb_disable_underglow = 0;
            #endif  // ID67_DISABLE_UNDERGLOW
        }
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
        id67_set_rgb_mode();
    }
    return false;
}

static bool id67_toggle_caps_lock(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_disable_capslock ^= 1;
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
    }
    return false;
}

static bool id67_toggle_per_key(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_disable_perkey ^= 1;
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
        id67_set_rgb_mode();
    }
    return false;
}

#ifndef ID67_DISABLE_UNDERGLOW
static bool id67_toggle_underglow(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_disable_underglow ^= 1;
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
        id67_set_rgb_mode();
    }
    return false;
}
#endif  // ID67_DISABLE_UNDERGLOW

#endif  // RGB_MATRIX_ENABLE

bool process_record_id67(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef RGB_MATRIX_ENABLE
        case RGB_TOG: return id67_toggle_rgb(record); break;
        case KC_TOGGLE_CAPS_LOCK_LED: return id67_toggle_caps_lock(record); break;
        case RGB_TOGGLE_PER_KEY: return id67_toggle_per_key(record); break;
        #ifndef ID67_DISABLE_UNDERGLOW
        case RGB_TOGGLE_UNDERGLOW: id67_toggle_underglow(record); break;
        #endif  // ID67_DISABLE_UNDERGLOW
        #endif  // RGB_MATRIX_ENABLE

        default: break;
    }

    return true;
}
