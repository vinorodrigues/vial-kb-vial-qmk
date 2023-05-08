// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "idobao_common.h"
#include "id67_common.h"

#define LT1_C_L LT(1, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backspc│ ~ │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │*Caps*│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │PUp│  *Caps* => `LT(1, KC_CAPS)`
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shft │Up │PDn│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │Ctrl│Opt │Comm│                        │Fn1 │Fn2 │ │Lf │Dn │Rt │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [0] = LAYOUT_65_ansi_blocker(
        QK_GESC,  KC_1,     KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,  KC_BSPC,   KC_GRAVE,
        KC_TAB,   KC_Q,     KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,   KC_RBRC, KC_BSLS,   KC_DELETE,
        LT1_C_L,  KC_A,     KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,    KC_PGUP,
        KC_LSFT,            KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT, KC_UP,     KC_PGDN,
        KC_LCTL,  KC_LALT,           KC_LGUI,                    KC_SPC,                             FN_MO13, FN_MO23,   KC_LEFT, KC_DOWN,   KC_RIGHT),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │ ~ │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│ ERASE │F13│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │Up │   │   │   │   │   │   │   │PSc│Hom│End│Eject│Ins│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │Lf │Dn │Rt │   │   │   │   │   │   │PUp│PDn│ enter  │Hom│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │  Shft  │   │   │   │   │   │   │   │   │Ins│Del│Shift │   │End│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │ctrl│opt │comm│                        │    │Fn3 │ │   │   │   │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRAVE, KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_ERAS,   KC_F13,
        _______,  XXXXXXX,  KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_HOME,   KC_END,  KC_EJCT,   KC_INS,
        KC_CAPS,  KC_LEFT,  KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN,            KC_PENT,   KC_HOME,
        KC_RSFT,            XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_DELETE, KC_LSFT, _______,   KC_END,
        KC_RCTL,  KC_RALT,           KC_RGUI,                    _______,                            _______, _______,   _______, _______,   _______),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│SB-│SB+│mMC│mLP│Br-│Br+│Prv│Ply│Nxt│Mut│Vl-│Vl+│  out  │F14│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tog │Mod│   │   │   │   │   │   │   │   │   │   │   │     │PSc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │mod│   │   │   │   │   │   │   │   │Hu+│Sa+│        │SLk│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │   │   │   │   │   │Hu-│Sa-│      │Br+│Pau│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │                        │Fn3 │    │ │Sp-│Br-│Sp+│
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [2] = LAYOUT_65_ansi_blocker(
        KC_ESC,   KC_BRID,  KC_BRIU, KC_MCTL,  KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,   KC_VOLU, KC_OUT,    KC_F14,
        RGB_TOG,  RGB_MOD,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,   KC_PSCR,
        XXXXXXX,  RGB_RMOD, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI,            XXXXXXX,   KC_SCRL,
        XXXXXXX,            XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD,   XXXXXXX, RGB_VAI,   KC_PAUS,
        XXXXXXX,  XXXXXXX,           XXXXXXX,                    XXXXXXX,                            XXXXXXX, XXXXXXX,   RGB_SPD, RGB_VAD,   RGB_SPI),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │RST│M01│M02│M03│M04│M05│M06│M07│M08│M09│M10│M11│M12│ Power │F15│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │Sleep│   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │ Debug  │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │   │   │   │Ver│   │   │   │   │   │   │      │M00│   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │          Wake          │    │    │ │M13│M14│M15│
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [3] = LAYOUT_65_ansi_blocker(
        QK_BOOT,  MACRO01,  MACRO02, MACRO03, MACRO04, MACRO05, MACRO06, MACRO07, MACRO08, MACRO09, MACRO10, MACRO11,   MACRO12, KC_PWR,    MACRO15,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_SLEP,   XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            DB_TOGG,   XXXXXXX,
        XXXXXXX,            QK_BOOT, XXXXXXX, XXXXXXX, KC_VERS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, MACRO00,   XXXXXXX,
        XXXXXXX,  XXXXXXX,           XXXXXXX,                   KC_WAKE,                            XXXXXXX, XXXXXXX,   MACRO13, MACRO14,   MACRO15)
};

/*
 * Keycode stuff
 */

void housekeeping_task_user(void) {
    housekeeping_task_idobao();
}

void keyboard_post_init_user(void) {
    keyboard_post_init_id67();
}

void eeconfig_init_user(void) {
    eeconfig_init_id67();
}

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return rgb_matrix_indicators_advanced_id67(led_min, led_max);
}

#endif

/*
 * Process Record
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_idobao(keycode, record)) { return false; }
    if (!process_record_id67(keycode, record)) { return false; }
    return true;  // Process all other keycodes normally
}
