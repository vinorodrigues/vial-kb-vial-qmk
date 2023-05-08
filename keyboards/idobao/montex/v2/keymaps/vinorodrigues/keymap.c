// Copyright 2022 IBNobody (@IBNobody)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "idobao_common.h"
#include "id27_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐
     * │Esc│Mut│VUp│VDn│Bsp│
     * ├───┼───┼───┼───┼───┤
     * │Ctr│Num│ / │ * │ - │
     * ├───┼───┼───┼───┼───┤
     * │Gui│Hom│ ↑ │PgU│   │
     * ├───┼───┼───┼───┤ + │
     * │Alt│ ← │   │ → │   │
     * ├───┼───┼───┼───┼───┤
     * │Shi│End│ ↓ │PgD│   │
     * ├───┼───┴───┼───┤Ent│
     * │MO1│  Ins  │Del│   │
     * └───┴───────┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_BSPC,
        KC_LCTL, TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_LGUI, KC_HOME, KC_UP,   KC_PGUP, KC_PPLS,
        KC_LALT, KC_LEFT, XXXXXXX, KC_RGHT,
        KC_LSFT, KC_END,  KC_DOWN, KC_PGDN, KC_ENT,
        MO(2),   KC_INS,           KC_DEL
    ),

    /*
     * ┌───┬───┬───┬───┬───┐
     * │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┤
     * │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┤
     * │   │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┼───┤   │
     * │   │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤───┤
     * │   │ 1 │ 2 │ 3 │   │
     * ├───┼───┴───┼───┤Ent│
     * │   │   0   │ . │   │
     * └───┴───────┴───┴───┘
     */
    [1] = LAYOUT(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, KC_P7,   KC_P8,   KC_P9,   _______,
        _______, KC_P4,   KC_P5,   KC_P6,
        _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        _______, KC_P0,            KC_DOT
    ),

    /*
     * ┌───┬───┬───┬───┬───┐
     * │Rst│TOG│MOD│PSs│SLk│
     * ├───┼───┼───┼───┼───┤
     * │Hu+│   │Sp-│Sp+│Br-│
     * ├───┼───┼───┼───┼───┤
     * │Hu-│Hom│ ↑ │PgU│   │
     * ├───┼───┼───┼───┤Br+│
     * │St+│ ← │   │ → │   │
     * ├───┼───┼───┼───┤───┤
     * │St-│End│ ↓ │PgD│   │
     * ├───┼───┴───┼───┤Ent│
     * │   │Insert │Del│   │
     * └───┴───────┴───┴───┘
     */
    [2] = LAYOUT(
        QK_BOOT, RGB_TOG, RGB_MOD, RGB_TPK, RGB_TUG,
        RGB_HUI, KC_NLED, RGB_SPD, RGB_SPI, RGB_VAD,
        RGB_HUD, KC_HOME, KC_UP,   KC_PGUP, RGB_VAI,
        RGB_SAI, KC_LEFT, XXXXXXX, KC_RGHT,
        RGB_SAD, KC_END,  KC_DOWN, KC_PGDN, KC_ENT,
        _______, KC_INS,           KC_DEL
    ),

    /*  extra layers incase you want to map the top row to layer buttons
     * ┌───┬───┬───┬───┬───┐
     * │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┤
     * │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┤
     * │   │   │   │   │   │
     * ├───┼───┼───┼───┤   │
     * │   │   │   │   │   │
     * ├───┼───┼───┼───┤───┤
     * │   │   │   │   │   │
     * ├───┼───┴───┼───┤   │
     * │   │       │   │   │
     * └───┴───────┴───┴───┘
     */
    [3] = LAYOUT(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______
    ),

    [4] = LAYOUT(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______
    ),

    [5] = LAYOUT(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______
    )
};

/*
 * Keycode stuff
 */

void housekeeping_task_user(void) {
    housekeeping_task_idobao();
}

void keyboard_post_init_user(void) {
    keyboard_post_init_id27();
}

void eeconfig_init_user(void) {
    eeconfig_init_id27();
}

#ifdef RGB_MATRIX_ENABLE

/*
 * RGB Stuff
 */

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return rgb_matrix_indicators_advanced_id27(led_min, led_max);
}

#endif

/*
 * Process Record
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_idobao(keycode, record)) { return false; }
    if (!process_record_id27(keycode, record)) { return false; }
    return true;  // Process all other keycodes normally
}
