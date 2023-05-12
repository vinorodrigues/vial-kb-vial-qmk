// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "idobao_common.h"
#include "id61_common.h"

#define KC_LT1C LT(1, KC_CAPS)  // Layer Tap 1, i.e., Tap = Caps Lock, Hold = Layer 1
#define KC_LT2A LT(2, KC_APP)   // Layer Tap 2, i.e., Tap = Menu, Hold = Layer 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Backspc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │*Caps*│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │  *Caps* => Tap = Caps Lock, Hold = Layer 1 (Fn1)
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  ↑Shift  │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │Ctrl│Opt │Cmd │                        │Fn1 │←Cmd│↓Opt│→Ctl│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [0] = LAYOUT_60_ansi(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LT1C, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_S_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             MO(1),    KC_G_LF, KC_A_DN, KC_C_RT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │ ~ │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  Del  │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ArwMd│   │ ↑ │   │   │Tog│Hu+│Sa+│Br+│Sp+│PSc│Hom│End│ Ins │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │ ← │ ↓ │ → │   │Mod│Hu-│Sa-│Br-│Sp-│   │PUp│        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │Ver│Rst│NKR│   │   │   │PDn│     ↑    │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │Fn3 │Fn2 │                        │    │  ← │  ↓ │  → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_ARRW, _______,  KC_UP,    _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_PSCR, KC_HOME, KC_END,  KC_INS,
        _______, KC_LEFT,  KC_DOWN,  KC_RGHT, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, KC_PGUP, _______,
        _______,           _______,  _______, EE_CLR,  KC_VERS, QK_BOOT, NK_TOGG, _______, _______, _______, KC_PGDN, _______,
        _______, MO(3),    MO(2),                               _______,                            _______, _______, _______, _______
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │m00│m01│m02│m03│m04│m05│m06│m07│m08│m09│m10│m11│m12│ m13   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │        │   │   │   │   │   │   │   │   │   │   │          │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │    │    │    │                        │    │    │    │    │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [2] = LAYOUT_60_ansi(
        MACRO00, MACRO01, MACRO02, MACRO03, MACRO04, MACRO05, MACRO06, MACRO07, MACRO08, MACRO09, MACRO10, MACRO11, MACRO12, MACRO13,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),

    [3] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    )
};

/*
 * Keycode stuff
 */

void housekeeping_task_user(void) {
    housekeeping_task_idobao();
}

void keyboard_post_init_user(void) {
    keyboard_post_init_id61();
}

void eeconfig_init_user(void) {
    eeconfig_init_id61();
}

/*
 * RGB Stuff
 */

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return rgb_matrix_indicators_advanced_id61(led_min, led_max);
}
#endif

/*
 * Process Record
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // if (!process_record_idobao(keycode, record)) { return false; }  // Don't call `process_record_idobao`
    if (!process_record_id61(keycode, record)) { return false; }

    #ifdef RGB_MATRIX_ENABLE
    switch (keycode) {
        case QK_BOOT:
            if (record->event.pressed) {
                rgb_matrix_driver.set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, 0, 0);  // All red
                rgb_matrix_driver.flush();
            }
            return true;

        case EE_CLR:
            if (record->event.pressed) {
                rgb_matrix_driver.set_color_all(RGB_MATRIX_MAXIMUM_BRIGHTNESS, (RGB_MATRIX_MAXIMUM_BRIGHTNESS * 0.65), 0);  // All orange
                rgb_matrix_driver.flush();
            }
            return true;
    }
    #endif  // RGB_MATRIX_ENABLE

    return true;  // Process all other keycodes normally
}
