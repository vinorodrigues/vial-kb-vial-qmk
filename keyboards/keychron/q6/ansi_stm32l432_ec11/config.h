// Copyright 2022 Keychron (https://www.keychron.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Keychron matrix.c */
#define DATA_PIN_74HC595 C15  // Pin connected to DS of 74HC595
#define CLOCK_PIN_74HC595 A1  // Pin connected to SH_CP of 74HC595
#define LATCH_PIN_74HC595 A0  // Pin connected to ST_CP of 74HC595
#define PIN_USED_74HC595 10   // Pin used number of 74HC595
#define PIN_START_74HC595 10  // Pin used index start of 74HC595

/* DIP switch */
#define DIP_SWITCH_MATRIX_GRID  { {5, 4} }
#define SCAN_COUNT_MAX 100

/* RGB Matrix Driver Configuration */
#define DRIVER_COUNT 2
#define DRIVER_ADDR_1 0b1110111
#define DRIVER_ADDR_2 0b1110100

/* Scan phase of led driver set as MSKPHASE_9CHANNEL(defined as 0x03 in CKLED2001.h) */
#define PHASE_CHANNEL MSKPHASE_9CHANNEL
#define CKLED2001_CURRENT_TUNE { 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52, 0xA4, 0xA4, 0x52 }

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 60
#define DRIVER_2_LED_TOTAL 48
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define DRIVER_LED_TOTAL (RGB_MATRIX_LED_COUNT)  // legacy

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 62

/* Enable num-lock LED */
#define NUM_LOCK_LED_INDEX 37

/* Enable scroll-lock LED */
#define SCROLL_LOCK_LED_INDEX 14  // todo: test this
