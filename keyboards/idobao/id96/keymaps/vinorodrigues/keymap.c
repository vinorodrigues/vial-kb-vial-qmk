// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "idobao_common.h"

enum {
    _L0 = 0,
    _L1,
    _L2
};

#define KC_NUMLK KC_NUM_LOCK

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_SNAP, KC_SIRI, KC_MPLY,  KC_MUTE, KC_VOLD, KC_VOLU,
        KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, TG(_L1),  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,          KC_HOME,  KC_UP,   KC_PGUP, XXXXXXX,
        KC_CAPS, KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,                    KC_LEFT,  XXXXXXX, KC_RGHT, KC_PPLS,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,          XXXXXXX, KC_END,   KC_DOWN, KC_PGDN, XXXXXXX,
        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                             KC_RGUI,  KC_RALT, XXXXXXX, MO(_L2), KC_RCTL, XXXXXXX,  KC_INS,  KC_DEL,  KC_ENT
    ),

    [_L1] = LAYOUT(
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  _______, _______, _______,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, TG(_L1),  KC_PSLS, KC_PAST, KC_PMNS,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,          KC_P7,    KC_P8,   KC_P9,   _______,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______,                   KC_P4,    KC_P5,   KC_P6,   KC_PPLS,
        _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,  _______, _______,          _______, KC_P1,    KC_P2,   KC_P3,   _______,
        _______, _______, _______,                             _______,                            _______,  _______, _______, _______, _______, KC_RGHT,  KC_P0,   KC_PDOT, KC_PENT
    ),

    [_L2] = LAYOUT(
        QK_BOOT, KC_BRID, KC_BRIU, KC_MCTL,  KC_LPAD, BL_DEC,  BL_INC,  KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_F20,  KC_F21,  KC_F22,   KC_F23,  KC_F24,  KC_SLEP,
        MACRO00, MACRO01, MACRO02, MACRO03,  MACRO04, MACRO05, MACRO06, MACRO07, MACRO08, MACRO09, MACRO10, MACRO11, MACRO12, XXXXXXX, XXXXXXX, KC_NUMLK, KC_F13,  KC_F14,  KC_F15,
        BL_TOGG, BL_STEP, KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,  BL_INC,  XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_ON,   XXXXXXX,                   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, BL_STEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_OFF,  XXXXXXX,          XXXXXXX, XXXXXXX,  BL_DEC,  XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                             KC_WAKE,                            XXXXXXX, KC_APP,  XXXXXXX, _______, XXXXXXX, XXXXXXX,  KC_PSTE, KC_CUT,  XXXXXXX
    )
};

/*
 * KB lighting stuff
 */

void _show_caps_lock(bool show) {
    writePin( LED_CAPS_LOCK_PIN, !show );
}

void _show_num_lock(bool show) {
    writePin( LED_NUM_LOCK_PIN, !show );
}

layer_state_t layer_state_set_user(layer_state_t state) {
    _show_caps_lock( layer_state_cmp(state, _L2) );
    _show_num_lock( layer_state_cmp(state, _L1) );
    return state;
}

bool led_update_user(led_t led_state) {
    _show_caps_lock( layer_state_is(_L2) || led_state.caps_lock );
    _show_num_lock( layer_state_is(_L1) || led_state.num_lock );
    return false;
}

/*
 * Keycode stuff
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_idobao(keycode, record)) {
        return false;
    }

    return true;  /* Process all other keycodes normally */
}
