// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "idobao_common.h"
#include "id27_common.h"

#ifdef RGB_MATRIX_ENABLE

typedef union {
    uint8_t raw;
    struct {
        bool rgb_disable_perkey:1;
        bool rgb_disable_underglow:1;
        bool rgb_swap_numlock:1;
    };
} user_config_t;

user_config_t user_config = {.raw = 0};

static void id27_update_rgb_mode(void) {
    uint8_t flags = LED_FLAG_ALL;

    if (user_config.rgb_disable_perkey && user_config.rgb_disable_underglow) {
        flags = 0;  // All OFF Condition
    } else {
        if (user_config.rgb_disable_perkey) {
            flags = LED_FLAG_UNDERGLOW | 0xF0;
        }
        if (user_config.rgb_disable_underglow) {
            flags = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR | 0xF0;
        }
    }

    if (flags == 0) {
        rgb_matrix_set_flags(0);
        rgb_matrix_set_color_all(HSV_OFF);
    } else {
        rgb_matrix_set_flags(flags);
        rgb_matrix_enable_noeeprom();
    }

    eeconfig_update_kb(user_config.raw);  // write back to EEPROM
}

static void id27_get_rgb_mode(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    id27_update_rgb_mode();
}

bool id27_toggle_rgb(keyrecord_t *record) {
    /* roll through the LED modes
     * |    Level   | Per-key | Underglow |
     * |------------|---------|-----------|
     * | 0 (defalt) |   on    |    on     |
     * |     1      |   OFF   |    on     |
     * |     2      |   on    |    OFF    |
     * |     3      |   OFF   |    OFF    |
     */
    if (record->event.pressed) {
        if ( (!user_config.rgb_disable_perkey) && (!user_config.rgb_disable_underglow) ) {
            user_config.rgb_disable_perkey = 1;
        } else if ( user_config.rgb_disable_perkey && (!user_config.rgb_disable_underglow) ) {
            user_config.rgb_disable_perkey = 0;
            user_config.rgb_disable_underglow = 1;
        } else if ( (!user_config.rgb_disable_perkey) && user_config.rgb_disable_underglow ) {
            user_config.rgb_disable_perkey = 1;
        } else {
            user_config.rgb_disable_perkey = 0;
            user_config.rgb_disable_underglow = 0;
        }
        id27_update_rgb_mode();
    }
    return false;
}

static bool id27_toggle_num_lock(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_swap_numlock ^= 1;
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
    }
    return false;
}

static bool id27_toggle_per_key(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_disable_perkey ^= 1;
        id27_update_rgb_mode();
    }
    return false;
}

static bool id27_toggle_underglow(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_disable_underglow ^= 1;
        id27_update_rgb_mode();
    }
    return false;
}

bool rgb_matrix_indicators_advanced_id27(uint8_t led_min, uint8_t led_max) {
    // (Windows) Num-Lock indicator is handled in `idobao_common.c`
    // This manages the Mac-emulated layer Num-Lock functionality

    #if defined(ID27_EMULATED_NUM_LOCK_LAYER) && defined(NUM_LOCK_LED_INDEX)

    bool on = layer_state_is(ID27_EMULATED_NUM_LOCK_LAYER);
    if (user_config.rgb_swap_numlock) { on = !on; }

    if (on) {
        uint8_t v = light_brightness_get();
        rgb_matrix_set_color( NUM_LOCK_LED_INDEX, v, v, v );
    }

    #endif

    return true;
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_id27(void) {
    #ifdef RGB_MATRIX_ENABLE
    id27_get_rgb_mode();
    #endif  // RGB_MATRIX_ENABLE
}

void eeconfig_init_id27(void) {
    // EEPROM is getting reset!
    #ifdef RGB_MATRIX_ENABLE
    user_config.raw = 0;
    id27_update_rgb_mode();
    #endif  // RGB_MATRIX_ENABLE
}

bool process_record_id27(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef RGB_MATRIX_ENABLE
        case RGB_TOG: return id27_toggle_rgb(record); break;
        case KC_NUM_LOCK_LED: return id27_toggle_num_lock(record); break;
        case RGB_TOGGLE_PER_KEY: return id27_toggle_per_key(record); break;
        case RGB_TOGGLE_UNDERGLOW: id27_toggle_underglow(record); break;

        case EE_CLR:
            if (!record->event.pressed) {  // on release
                id27_get_rgb_mode();
            }
            return true;  // let this one pass on
        #endif  // RGB_MATRIX_ENABLE

        default: break;
    }
    return true;
}
