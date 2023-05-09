// Copyright (c) 2021 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "v3.h"
#include "string.h"
#include "version.h"

enum custom_key_codes {
    KC_MCTL = USER00,  // Misson Control
    KC_LPAD,           // Launch Pad
    KC_APPL,           // Apple Fn / Globe
    KC_VERS            // Type version
};

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to KC_MCTL
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to KC_LPAD
};

#define LT1_C_L LT(1, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_GESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRAVE,
        KC_TAB,   KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DELETE,
        LT1_C_L,  KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT,  KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL,  KC_LALT,  KC_LGUI,                   KC_SPC,                    FN_MO13,          FN_MO23, KC_LEFT,          KC_DOWN, KC_RIGHT ),

    [1] = LAYOUT_65_ansi_blocker(
        KC_GRAVE, KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_ERAS, KC_F13,
        _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EJCT, KC_INS,
        KC_CAPS,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PENT, KC_HOME,
        KC_RSFT,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_END,
        KC_RCTL,  KC_RALT,  KC_RGUI,                   _______,                   _______,          _______, _______,          _______, _______ ),

    [2] = LAYOUT_65_ansi_blocker(
        KC_ESC,   KC_BRID,  KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_OUT,  KC_F14,
        RGB_TOG,  RGB_MOD,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
        XXXXXXX,  RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI,          XXXXXXX, KC_SLCK,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, XXXXXXX,          RGB_VAI, KC_PAUS,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                   XXXXXXX,                   XXXXXXX,          XXXXXXX, RGB_SPD,          RGB_VAD, RGB_SPI ),

    [3] = LAYOUT_65_ansi_blocker(
        QK_BOOT,  MACRO01,  MACRO02, MACRO03, MACRO04, MACRO05, MACRO06, MACRO07, MACRO08, MACRO09, MACRO10, MACRO11, MACRO12, KC_PWR,  KC_F15,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP, XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          DB_TOGG, XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, KC_VERS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          MACRO00, XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                   KC_WAKE,                   XXXXXXX,          XXXXXXX, MACRO13,          MACRO14, MACRO15 )
};

/*
 * RGB Stuff
 */

typedef union {
    uint8_t raw;
    struct {
        bool rgb_disable:1;
    };
} user_config_t;

user_config_t user_config = {.raw = 0};

#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator

const uint8_t g_led_config_new_flags[RGB_MATRIX_LED_COUNT] = {
    0x21, 0x04, 0x04, 0x04, 0x04, 0x24, 0x24, 0x24, 0x24, 0x04, 0x04, 0x04, 0x04, 0x01, 0x21,
    0x21, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04, 0x21,
    0x29, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04,       0x01, 0x21,
    0x21, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04, 0x01,       0x01, 0x21,
    0x21, 0x01, 0x01,             0x04,             0x01,       0x01, 0x01,       0x01, 0x21 };

static void __write_eeprom(void) {
    eeconfig_update_user(user_config.raw);
}

static void __set_rgb_mode(void) {
    if (user_config.rgb_disable) {
        rgb_matrix_set_flags(LED_FLAG_INDICATOR | LED_FLAG_LAYER_IND);
        rgb_matrix_set_color_all(0, 0, 0);
    } else {
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_enable_noeeprom();
    }
}

static void __read_eeprom(void) {
    user_config.raw = eeconfig_read_user();
}

void keyboard_pre_init_user(void) {
    // override `info.json` flags with new values
    memcpy(g_led_config.flags, g_led_config_new_flags, RGB_MATRIX_LED_COUNT);
}

void keyboard_post_init_user(void) {
    __read_eeprom();
}

void eeconfig_init_user(void) {
    user_config.raw = 0;  // reset
    __write_eeprom();
    __set_rgb_mode();
}

bool rgb_matrix_indicators_user(void) {
    /* do nothing, but override existing white light function */
    return false;
}

static bool isCapsBlink = false;
static uint32_t recording_timer;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    uint8_t v = light_brightness_get();
    uint8_t current_layer = get_highest_layer(layer_state);
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    // Caps Lock key stuff

    if (host_keyboard_led_state().caps_lock) {
        if (user_config.rgb_disable) {
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v);  // white
        } else {
            // Caps Lock key/LED blink code
            if (timer_elapsed32(recording_timer) > 500) {
                isCapsBlink = !isCapsBlink;
                recording_timer = timer_read32();
            }
            if (isCapsBlink) {
                rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v);  // white
            }

            // Alpha keys/LEDs
            for (uint8_t i = led_min; i <= led_max; i++) {
                if (g_led_config.flags[i] & LED_FLAG_ALPHA_KEY) {
                    rgb_matrix_set_color(i, v, 0, 0);  // red
                }
            }
        }
    } else if (user_config.rgb_disable) {
        switch (current_layer) {
            case 1: b = v; break;
            case 2: g = v; break;
            case 3: r = v; break;
            default: break;
        }
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, r, g, b);
    }

    // Layer indicator stuff

    if (current_layer > 0) {
        switch (current_layer) {
            case 1: b = v; break;
            case 2: g = v; break;
            case 3: r = v; break;
            default: break;
        }
    }

    if ((current_layer > 0) || user_config.rgb_disable) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if ((g_led_config.flags[i] & LED_FLAG_LAYER_IND) != 0) {
                rgb_matrix_set_color(i, r, g, b);
            }
        }
    }

    return true;
}

/*
 * Keycode stuff
 */

static bool __rgb_toggle(keyrecord_t *record) {
    if (record->event.pressed) {
        user_config.rgb_disable = !user_config.rgb_disable;
        __set_rgb_mode();
        __write_eeprom();
    }
    return false;
}

static bool __do_version(keyrecord_t *record) {
    if (!get_mods()) {
        if (!record->event.pressed) {
            SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " (v" QMK_VERSION ")");
        }
    }
    return false;
}

static bool __host_consumer_send(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        host_consumer_send(data);
    } else {
        host_consumer_send(0);
    }
    return false;  // Skip all further processing of this key
}

static bool __register_code(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        register_code(data);
    } else {
        unregister_code(data);
    }
    return false;  // Skip all further processing of this key
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        #ifdef RGB_MATRIX_ENABLE
        case RGB_TOG: return __rgb_toggle(record); break;
        #endif
        case KC_VERS: return __do_version(record); break;
        case KC_MCTL: return __host_consumer_send(record, _AC_SHOW_ALL_WINDOWS); break;
        case KC_LPAD: return __host_consumer_send(record, _AC_SHOW_ALL_APPS); break;
        case KC_APPL: return __register_code(record, KC_APPLE_FN); break;
        default: break;
    }

    return true;  // Process all other keycodes normally
}
