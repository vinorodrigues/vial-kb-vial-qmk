// Copyright (c) 2021 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x78, 0x8C, 0x74, 0x8D, 0x32, 0x59, 0xE8, 0x30}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

#if defined(RGB_MATRIX_ENABLE)
    #define VIA_QMK_RGBLIGHT_ENABLE true
    #define RGB_MATRIX_KEYPRESSES

    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN   // Static gradient top to bottom, speed controls how much gradient changes
    // #define ENABLE_RGB_MATRIX_BAND_SAT           // Single hue band fading saturation scrolling left to right
    // #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT  // Single hue 3 blade spinning pinwheel fades saturation
    // #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT    // Single hue spinning spiral fades saturation

    // #undef ENABLE_RGB_MATRIX_PIXEL_RAIN
    // #undef ENABLE_RGB_MATRIX_PIXEL_FLOW
    #undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP

    // enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE      // Pulses keys hit to hue & value then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE             // Static single hue, pulses keys hit to shifted hue then fades to current hue
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE        // Hue & value pulse near a single key hit then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE   // Hue & value pulse near multiple key hits then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS       // Hue & value pulse the same column and row of a single key hit then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS  // Hue & value pulse the same column and row of multiple key hits then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS       // Hue & value pulse away on the same column and row of a single key hit then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    // #define ENABLE_RGB_MATRIX_SPLASH                     // Full gradient & value pulse away from a single key hit then fades value out
    // #define ENABLE_RGB_MATRIX_MULTISPLASH                // Full gradient & value pulse away from multiple key hits then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_SPLASH               // Hue & value pulse away from a single key hit then fades value out
    // #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH          // Hue & value pulse away from multiple key hits then fades value out
#endif
