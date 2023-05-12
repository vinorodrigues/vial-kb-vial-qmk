// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "string.h"
#include "idobao_common.h"
#include "id61_common.h"

#ifdef RGB_MATRIX_ENABLE
#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator
#endif

typedef union {
    uint32_t raw;
    struct {
        bool in_arrow_mode:1;
        #ifdef RGB_MATRIX_ENABLE
        bool rgb_disable_perkey:1;
        #ifndef ID61_DISABLE_UNDERGLOW
        bool rgb_disable_underglow:1;
        #endif  // ID61_DISABLE_UNDERGLOW
        // bool rgb_disable_capslock:1;
        #endif  // RGB_MATRIX_ENABLE
    };
} user_config_t;

#ifdef RGB_MATRIX_ENABLE
const uint8_t g_led_config_new_flags[RGB_MATRIX_LED_COUNT] = {
    0x01, 0x01, 0x01, 0x01,                   0x04,                   0x01, 0x01, 0x01,
    0x01,       0x04, 0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x01,
    0x01, 0x01, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x09,
    0x01, 0x04, 0x04, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x01,
    0x01, 0x01, 0x04, 0x04, 0x04, 0x24, 0x24, 0x24, 0x24, 0x04, 0x04, 0x04, 0x04, 0x04
    #ifndef ID61_DISABLE_UNDERGLOW
    , 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02
    #endif
};
#endif

user_config_t user_config = {.raw = 0};
uint32_t _keycode_raised = 0;
bool _delete_key_raised = false;
#ifdef RGB_MATRIX_ENABLE
bool led_on_lyr = false;
#endif

#ifdef RGB_MATRIX_ENABLE
void keyboard_pre_init_kb(void) {
    // override `info.json` flags with new values
    memcpy(g_led_config.flags, g_led_config_new_flags, RGB_MATRIX_LED_COUNT);
}
#endif

bool get_keycode_raised(uint8_t n) {
    return _keycode_raised & (1 << n);
}

void set_keycode_raised(uint8_t n, bool b) {
    if (b) { _keycode_raised |= 1 << n; }
    else { _keycode_raised &= ~(1 << n); }
}

static bool id61_process_special_k(uint16_t keycode, keyrecord_t *record, bool arrow_mode, uint8_t k_norm, uint8_t k_spcl, uint8_t k_altr) {
    bool is_raised = get_highest_layer(layer_state|default_layer_state) != 0;

    if (record->event.pressed) {
        set_keycode_raised(keycode - QK_KB_0, is_raised);  // save for key release event
        if (is_raised) {
            // *** Fn keyed ***
            if (arrow_mode) {
                // alternate key
                register_code(k_altr);
            } else {
                // special key
                register_code(k_spcl);
            }
        } else {
            // *** normal, un-Fn'ed ***
            if (arrow_mode) {
                // special key
                register_code(k_spcl);
            } else {
                // normal key
                register_code(k_norm);
            }
        }
    } else {
        if (get_keycode_raised(keycode - QK_KB_0)) {
            // *** Fn keyed ***
            if (arrow_mode) {
                // alternate key
                unregister_code(k_altr);
            } else {
                // special key
                unregister_code(k_spcl);
            }
        } else {
            // *** normal, un-Fn'ed ***
            if (arrow_mode) {
                // special key
                unregister_code(k_spcl);
            } else {
                // normal key
                unregister_code(k_norm);
            }
        }
    }
    return false;
}

bool id61_backspace_special(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();

    if (record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            register_code(KC_DEL);
            _delete_key_raised = true;
            set_mods(mod_state);
            return false;
        }
    } else {
        if (_delete_key_raised) {
            _delete_key_raised = false;
            unregister_code(KC_DEL);
            return false;
        }
    }
    return true;  // normal backspace, pass on
}

#ifdef RGB_MATRIX_ENABLE

static void id61_set_rgb_mode(void) {
    uint8_t flags = LED_FLAG_ALL;

    if (user_config.rgb_disable_perkey
        #ifndef ID61_DISABLE_UNDERGLOW
        && user_config.rgb_disable_underglow
        #endif  // ID61_DISABLE_UNDERGLOW
        ) {
        flags = 0;  // All OFF Condition
    } else {
        if (user_config.rgb_disable_perkey) {
            flags = LED_FLAG_UNDERGLOW | 0xF0;
        }
        #ifndef ID61_DISABLE_UNDERGLOW
        if (user_config.rgb_disable_underglow) {
            flags = LED_FLAG_MODIFIER | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR | 0xF0;
        }
        #endif  // ID61_DISABLE_UNDERGLOW
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

void keyboard_post_init_id61(void) {
    user_config.raw = eeconfig_read_kb();  // read config from EEPROM
    #ifdef RGB_MATRIX_ENABLE
    id61_set_rgb_mode();
    #endif  // RGB_MATRIX_ENABLE
}

void eeconfig_init_id61(void) {
    // EEPROM is getting reset!
    #ifdef RGB_MATRIX_ENABLE
    user_config.raw = 0;
    id61_set_rgb_mode();
    #endif  // RGB_MATRIX_ENABLE
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_id61(uint8_t led_min, uint8_t led_max) {
    uint8_t v = rgb_matrix_get_val();

    if ((v > 0) && (!user_config.rgb_disable_perkey) && host_keyboard_led_state().caps_lock) {
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
#endif

static bool id61_toggle_arrow_mode(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.in_arrow_mode ^= 1;
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
    }
    return false;
}

#ifdef RGB_MATRIX_ENABLE
static bool id61_toggle_rgb(keyrecord_t *record) {
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
            #ifndef ID61_DISABLE_UNDERGLOW
            && (!user_config.rgb_disable_underglow)
            #endif  // ID61_DISABLE_UNDERGLOW
            ) {
            user_config.rgb_disable_perkey = 1;
        #ifndef ID61_DISABLE_UNDERGLOW
        } else if ( user_config.rgb_disable_perkey && (!user_config.rgb_disable_underglow) ) {
            user_config.rgb_disable_perkey = 0;
            user_config.rgb_disable_underglow = 1;
        } else if ( (!user_config.rgb_disable_perkey) && user_config.rgb_disable_underglow ) {
            user_config.rgb_disable_perkey = 1;
        #endif  // ID61_DISABLE_UNDERGLOW
        } else {
            user_config.rgb_disable_perkey = 0;
            #ifndef ID61_DISABLE_UNDERGLOW
            user_config.rgb_disable_underglow = 0;
            #endif  // ID61_DISABLE_UNDERGLOW
        }
        eeconfig_update_kb(user_config.raw);  // write back to EEPROM
        id61_set_rgb_mode();
    }
    return false;
}
#endif

bool process_record_id61(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MISSION_CONTROL_2: return idobao_host_consumer_send(record, _AC_SHOW_ALL_WINDOWS); break;
        case KC_LAUNCHPAD_2:       return idobao_host_consumer_send(record, _AC_SHOW_ALL_APPS); break;

        case KC_TOGGLE_ARROW_MODE: return id61_toggle_arrow_mode(record); break;

        case KC_RSHIFT_OR_UP:  return id61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RSFT, KC_UP, KC_PGUP); break;
        case KC_RALT_OR_LEFT:  return id61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RALT, KC_LEFT, KC_HOME); break;
        case KC_APP_OR_DOWN:   return id61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_APP, KC_DOWN, KC_PGDN); break;
        case KC_RGUI_OR_LEFT:  return id61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RGUI, KC_LEFT, KC_HOME); break;
        case KC_RALT_OR_DOWN:  return id61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RALT, KC_DOWN, KC_PGDN); break;
        case KC_RCTL_OR_RIGHT: return id61_process_special_k(keycode, record, user_config.in_arrow_mode, KC_RCTL, KC_RIGHT, KC_END); break;

        #ifdef RGB_MATRIX_ENABLE
        case RGB_TOG: return id61_toggle_rgb(record); break;
        // case KC_TOGGLE_CAPS_LOCK_LED: return id67_toggle_caps_lock(record); break;
        // case RGB_TOGGLE_PER_KEY: return id67_toggle_per_key(record); break;
        // #ifndef ID67_DISABLE_UNDERGLOW
        // case RGB_TOGGLE_UNDERGLOW: id67_toggle_underglow(record); break;
        // #endif  // ID67_DISABLE_UNDERGLOW
        #endif  // RGB_MATRIX_ENABLE

        case KC_VERSION_2: return idobao_print_version(record); break;

        default: break;
    }

    return true;
}
