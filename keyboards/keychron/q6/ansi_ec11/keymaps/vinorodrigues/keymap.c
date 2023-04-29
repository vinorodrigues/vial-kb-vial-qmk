// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "vinorodrigues_common.h"
#include "caffeine.h"
#include "dice.h"

// clang-format off

enum my_layers {
    MAC_BASE,
    MAC_NUML,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

#define KC_M_FN MO(MAC_FN)
#define KC_M_NL TG(MAC_NUML)
#define KC_M_FC LT(MAC_FN, KC_CAPS)
#define KC_W_FN LT(WIN_FN, KC_APP)
#define KC_W_FC LT(WIN_FN, KC_CAPS)

#define KK_LOPT KC_LOPTN
#define KK_ROPT KC_ROPTN
#define KK_LCMD KC_LCMMD
#define KK_RCMD KC_RCMMD
#define RGB_RMD RGB_RMOD

#ifdef CONSOLE_ENABLE
    #define _DEBUG_ DB_TOGG
#else
    #define _DEBUG_ _______
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_109(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_SNAP, KC_SIRI, RGB_TOG, KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_M_NL, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_HOME, KC_UP,   KC_PGUP, KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_LEFT, XXXXXXX, KC_RGHT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_END,  KC_DOWN, KC_PGDN, KC_ENT,
        KC_LCTL, KK_LOPT, KK_LCMD,                            KC_SPC,                             KK_RCMD, KK_ROPT, KC_M_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,           KC_DEL           ),

    [MAC_NUML] = LAYOUT_ansi_109(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            KC_P4,   KC_P5,   KC_P6,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,          KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, KC_P0,            KC_PDOT          ),

    [MAC_FN] = LAYOUT_ansi_109(
        _______, KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG, _______, _______, RGB_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, KC_CAFF, KC_DICE, _______,          _______,                            _______, _______, _______,
        _______,          QK_BOOT, _______, _______, KC_VRSN, _______, NK_TOGG, _______, _______, _______, _DEBUG_,          _______,          _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______,          _______          ),

    [WIN_BASE] = LAYOUT_ansi_109(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_PSCR, KC_CRTA, RGB_TOG, _______, _______, _______, _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LWIN, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RWIN, KC_W_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,            KC_PDOT          ),

    [WIN_FN] = LAYOUT_ansi_109(
        _______, KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG, _______, _______, RGB_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, KC_CAFF, KC_DICE, _______,          _______,                            _______, _______, _______,
        _______,          QK_BOOT, _______, _______, KC_VRSN, _______, NK_TOGG, _______, _______, _______, _DEBUG_,          _______,          _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______,           _______         )
};

// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_NUML] = { ENCODER_CCW_CW(_______, _______) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif  // ENCODER_MAP_ENABLE

// clang-format on


/* --------------
 * LED Indicators
 * -------------- */

#ifdef RGB_MATRIX_ENABLE

const uint8_t PROGMEM g_led_config_new_flags[DRIVER_LED_TOTAL] = {
    // Extended LED Index to Flag
    0x01, 0x01, 0x01, 0x01, 0x01, 0x21, 0x21, 0x21, 0x21, 0x01, 0x01, 0x01, 0x01,       0x01, 0x09, 0x01, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x01, 0x01, 0x01, 0x0C, 0x04, 0x04, 0x04,
    0x01, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04, 0x01, 0x01, 0x01, 0x04, 0x04, 0x04, 0x04,
    0x09, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04,       0x01,                   0x04, 0x04, 0x04,
    0x01,       0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04,       0x01,       0x01,       0x04, 0x04, 0x04, 0x04,
    0x01, 0x01, 0x01,                   0x04,                   0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,       0x04
};

static void __rgb_matrix_set_color_w(int index) {
    uint8_t v = light_brightness_get();
    rgb_matrix_set_color(index, v, v, v);
}

void keyboard_pre_init_user(void) {
    // override config.flags with new values
    memcpy(g_led_config.flags, g_led_config_new_flags, RGB_MATRIX_LED_COUNT);
    // for (int i = 0; i < DRIVER_LED_TOTAL; i++) g_led_config.flags[i] = g_led_config_new_flags[i];
}

bool rgb_matrix_indicators_user(void) {
    // don't call _keychron, that's already in `q6.c`
    if (!rgb_matrix_indicators_caffeine()) return false;
    if (!rgb_matrix_indicators_dice()) return false;

    if (MAC_NUML == get_highest_layer(layer_state)) {
        __rgb_matrix_set_color_w(NUM_LOCK_LED_INDEX);
    }

    return true;
}

bool led_update_user(led_t led_state) {
    if (!led_update_caffeine(led_state)) return false;
    if (!led_update_dice(led_state)) return false;

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
        return true;
    }

    if (MAC_NUML == get_highest_layer(layer_state)) {
        __rgb_matrix_set_color_w(NUM_LOCK_LED_INDEX);
    } else {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, HSV_OFF);
    }

    return true;
}

#endif  // RGB_MATRIX_ENABLE


/* ========================
 * KEYCHRON & VinoRodrigues
 * ======================== */

void keyboard_post_init_user(void) {
    keyboard_post_init_vinorodrigues();
    keyboard_post_init_caffeine();
    keyboard_post_init_dice();

    #ifdef CONSOLE_ENABLE
    /* DEBUG: Customise these values to desired behaviour */
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;
    #endif  // CONSOLE_ENABLE
}

void eeconfig_init_user(void) {
    // eeconfig_init_vinorodrigues();
    keyboard_post_init_user();
}

void matrix_scan_user(void) {
    matrix_scan_caffeine();
    matrix_scan_dice();
}

// Gets called at the end of all QMK processing, before starting the next iteration
void housekeeping_task_user(void) {
    housekeeping_task_keychron();
    housekeeping_task_vinorodrigues();
    housekeeping_task_caffeine();
    housekeeping_task_dice();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) return false;
    if (!process_record_vinorodrigues(keycode, record)) return false;

    switch (keycode) {
        case KC_CAFFEINE_TOGGLE: return caffeine_process_toggle_keycode(record);
        case KC_ROLL_DICE: return dice_process_toggle_keycode(record);
        default: return true;
    }
}

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        layer_state_set(1UL << (active ? WIN_BASE : MAC_BASE));
        default_layer_set(1UL << (active ? WIN_BASE : MAC_BASE));
        return false;
    }
    return true;
}
#endif  // DIP_SWITCH_ENABLE

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_keychron(led_min, led_max)) return false;
    if (!rgb_matrix_indicators_advanced_vinorodrigues(led_min, led_max)) return false;
    return true;
}
#endif  // RGB_MATRIX_ENABLE
