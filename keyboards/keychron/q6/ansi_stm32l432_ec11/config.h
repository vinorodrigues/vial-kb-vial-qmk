// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define KEYBOARD_keychron_q6_ansi_stm32l432_ec11

/* Keychron matrix.c */
#define DATA_PIN_74HC595 C15  // Pin connected to DS of 74HC595
#define CLOCK_PIN_74HC595 A1  // Pin connected to SH_CP of 74HC595
#define LATCH_PIN_74HC595 A0  // Pin connected to ST_CP of 74HC595
#define PIN_USED_74HC595 10  // Pin used number of 74HC595
#define PIN_START_74HC595 10  // Pin used index start of 74HC595

// #define NO_PIN_START 10
// #define NO_PIN_NUM 10
// #define CLR_REG_VAL 0x3FF

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {5, 4} }
#define SCAN_COUNT_MAX 100

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 60
#define DRIVER_2_LED_TOTAL 48
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (RGB_MATRIX_LED_COUNT)  // legacy, for Vial use

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock LED*/
#define CAPS_LOCK_LED_INDEX 62

/* Enable num-lock LED */
#define NUM_LOCK_LED_INDEX 37

/* Enable scroll-lock LED */
#define SCROLL_LOCK_LED_INDEX 14
