// Copyright 2022 Keychron(https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 45
#define DRIVER_2_LED_TOTAL 37
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (RGB_MATRIX_LED_COUNT)  // legacy, for Vial use

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 45
