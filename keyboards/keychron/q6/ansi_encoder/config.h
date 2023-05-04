// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 60
#define DRIVER_2_LED_TOTAL 48
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (RGB_MATRIX_LED_COUNT)  // legacy, for Vial use

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 62

/* Enable num-lock LED */
#define NUM_LOCK_LED_INDEX 37

/* Enable scroll-lock LED */
#define SCROLL_LOCK_LED_INDEX  14

#define SHIFT_COL_START 10
#define SHIFT_COL_END 19
