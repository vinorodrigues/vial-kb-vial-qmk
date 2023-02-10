// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#if defined(ENCODER_ENABLE) && defined(PAL_USE_CALLBACKS)

void encoder0_pad_cb(void *param) {
    (void)param;
    encoder_insert_state();
}

void keyboard_post_init_kb(void) {
    pin_t encoders_pad_a[NUM_ENCODERS] = ENCODERS_PAD_A;
    pin_t encoders_pad_b[NUM_ENCODERS] = ENCODERS_PAD_B;

    for (uint8_t i = 0; i < NUM_ENCODERS; i++) {
        palEnableLineEvent(encoders_pad_a[i], PAL_EVENT_MODE_BOTH_EDGES);
        palEnableLineEvent(encoders_pad_b[i], PAL_EVENT_MODE_BOTH_EDGES);
        palSetLineCallback(encoders_pad_a[i], encoder0_pad_cb, NULL);
        palSetLineCallback(encoders_pad_b[i], encoder0_pad_cb, NULL);
    }

    // allow user keymaps to do custom post_init
    keyboard_post_init_user();
}

#endif  // ENCODER_ENABLE
