// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

/* Vial */
#define VIAL_KEYBOARD_UID {0x0D, 0x74, 0x8A, 0xA6, 0x30, 0x70, 0x69, 0x69}  // copied from @adophoxia
// Unlock with Esc + Enter
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

/* Keymap Layer Count - we use 5 here */
#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Tap Code */
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAP_CODE_DELAY 10

/* EEPROM Driver Configuration */
#ifdef EXTERNAL_EEPROM_ENABLE
    #undef WEAR_LEVELING_LOGICAL_SIZE
    #undef WEAR_LEVELING_BACKING_SIZE
    // An assumption is made that a ST `M24C32-FMN6TP` 32Kbit module is used
    #define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100010  // Base I2C address for the EEPROM – shifted left by 1 as per i2c_master requirements
    #define EXTERNAL_EEPROM_BYTE_COUNT 4096              // Total size of the EEPROM in bytes
    // #define EXTERNAL_EEPROM_PAGE_SIZE 32                 // Page size of the EEPROM in bytes, as specified in the datasheet
    // #define EXTERNAL_EEPROM_ADDRESS_SIZE 2               // The number of bytes to transmit for the memory location within the EEPROM
    // #define EXTERNAL_EEPROM_WRITE_TIME 5                 // Write cycle time of the EEPROM, as specified in the datasheet
    // #undef EXTERNAL_EEPROM_WP_PIN                        // If defined the WP pin will be toggled appropriately when writing to the EEPROM.	none
#endif

/* used in `vinorodrigues_common.c` */
#define LED_COLOR_ALPHA_CAPS RGB_RED
#define LED_COLOR_LAYER_2 RGB_BLUE
#define LED_COLOR_LAYER_4 RGB_GREEN

/* used in `keymap.c` */
// #define CAFFEINE_KEY_DELAY 59000
// #define CAFFEINE_KEY_CODE KC_RIGHT_CTRL
#define CAFFEINE_LED_INDEX 95  // Left Ctrl
#define LED_COLOR_CAFFEINE RGB_PURPLE

// RGB Matrix Animation modes. Explicitly enabled
// `////` = already in base `config.h`

#define ENABLE_RGB_MATRIX_SOLID_COLOR               // Static single color
#define ENABLE_RGB_MATRIX_ALPHAS_MODS               // Static dual hue, speed is hue for secondary hue
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN          // Static gradient top to bottom, speed controls how much gradient changes
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT       // Static gradient left to right, speed controls how much gradient changes
//// #define ENABLE_RGB_MATRIX_BREATHING                 // Single hue brightness cycling animation
#define ENABLE_RGB_MATRIX_BAND_SAT                  // Single hue band fading saturation scrolling left to right
#define ENABLE_RGB_MATRIX_BAND_VAL                  // Single hue band fading brightness scrolling left to right
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT         // Single hue 3 blade spinning pinwheel fades saturation
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL         // Single hue 3 blade spinning pinwheel fades brightness
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT           // Single hue spinning spiral fades saturation
//// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL           // Single hue spinning spiral fades brightness
//// #define ENABLE_RGB_MATRIX_CYCLE_ALL                 // Full keyboard solid hue cycling through full gradient
//// #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT          // Full gradient scrolling left to right
//// #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN             // Full gradient scrolling top to bottom
//// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN              // Full gradient scrolling out to in
//// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL         // Full dual gradients scrolling out to in
//// #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON    // Full gradient Chevron shaped scrolling left to right
//// #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL            // Full gradient spinning pinwheel around center of keyboard
//// #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL              // Full gradient spinning spiral around center of keyboard
//// #define ENABLE_RGB_MATRIX_DUAL_BEACON               // Full gradient spinning around center of keyboard
//// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON            // Full tighter gradient spinning around center of keyboard
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS         // Full dual gradients spinning two halfs of keyboard
#define ENABLE_RGB_MATRIX_RAINDROPS                 // Randomly changes a single key's hue
//// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS       // Randomly changes a single key's hue and saturation
#define ENABLE_RGB_MATRIX_HUE_BREATHING             // Hue shifts up a slight amount at the same time, then shifts back
#define ENABLE_RGB_MATRIX_HUE_PENDULUM              // Hue shifts up a slight amount in a wave to the right, then back to the left
#define ENABLE_RGB_MATRIX_HUE_WAVE                  // Hue shifts up a slight amount and then back down in a wave to the right
// #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL	            // Enables RGB_MATRIX_PIXEL_FRACTAL
// #define ENABLE_RGB_MATRIX_PIXEL_FLOW	            // Enables RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN	            // Enables RGB_MATRIX_PIXEL_RAIN

/* RGB_MATRIX_FRAMEBUFFER_EFFECTS) */
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

/* RGB_MATRIX_KEYPRESSES) | defined(RGB_MATRIX_KEYRELEASES) */
//// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE     // Pulses keys hit to hue & value then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE            // Static single hue, pulses keys hit to shifted hue then fades to current hue
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
//// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
//// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
//// #define ENABLE_RGB_MATRIX_SPLASH                    // Full gradient & value pulse away from a single key hit then fades value out
#define ENABLE_RGB_MATRIX_MULTISPLASH               // Full gradient & value pulse away from multiple key hits then fades value out
//// #define ENABLE_RGB_MATRIX_SOLID_SPLASH              // Hue & value pulse away from a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH         // Hue & value pulse away from multiple key hits then fades value out
