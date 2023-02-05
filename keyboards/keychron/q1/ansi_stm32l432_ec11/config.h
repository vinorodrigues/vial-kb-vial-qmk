// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define KEYBOARD_keychron_q1_ansi_stm32l432_ec11

/* Keychron matrix.c */
#define DATA_PIN_74HC595 A7  // Pin connected to DS of 74HC595
#define CLOCK_PIN_74HC595 B1  // Pin connected to SH_CP of 74HC595
#define LATCH_PIN_74HC595 B0  // Pin connected to ST_CP of 74HC595

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {5,4} }

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 44
#define DRIVER_2_LED_TOTAL 37
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)  // new, Dec '22
#define DRIVER_LED_TOTAL (RGB_MATRIX_LED_COUNT)  // legacy, for Vial use

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 44
