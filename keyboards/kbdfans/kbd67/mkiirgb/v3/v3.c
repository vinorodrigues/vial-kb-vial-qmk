// Copyright 2021 DZTECH <moyi4681@live.cn>
// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "drivers/led/issi/is31fl3741.h"

#ifdef RGB_MATRIX_ENABLE

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, CS21_SW1, CS20_SW1, CS19_SW1},
    {0, CS21_SW2, CS20_SW2, CS19_SW2},
    {0, CS21_SW3, CS20_SW3, CS19_SW3},
    {0, CS21_SW4, CS20_SW4, CS19_SW4},
    {0, CS21_SW5, CS20_SW5, CS19_SW5},
    {0, CS21_SW6, CS20_SW6, CS19_SW6},
    {0, CS21_SW7, CS20_SW7, CS19_SW7},
    {0, CS21_SW8, CS20_SW8, CS19_SW8},
    {0, CS24_SW1, CS23_SW1, CS22_SW1},
    {0, CS24_SW2, CS23_SW2, CS22_SW2},
    {0, CS24_SW3, CS23_SW3, CS22_SW3},
    {0, CS24_SW4, CS23_SW4, CS22_SW4},
    {0, CS24_SW5, CS23_SW5, CS22_SW5},
    {0, CS24_SW6, CS23_SW6, CS22_SW6},
    {0, CS24_SW7, CS23_SW7, CS22_SW7},

    {0, CS15_SW1, CS14_SW1, CS13_SW1},
    {0, CS15_SW2, CS14_SW2, CS13_SW2},
    {0, CS15_SW3, CS14_SW3, CS13_SW3},
    {0, CS15_SW4, CS14_SW4, CS13_SW4},
    {0, CS15_SW5, CS14_SW5, CS13_SW5},
    {0, CS15_SW6, CS14_SW6, CS13_SW6},
    {0, CS15_SW7, CS14_SW7, CS13_SW7},
    {0, CS15_SW8, CS14_SW8, CS13_SW8},
    {0, CS30_SW1, CS29_SW1, CS28_SW1},
    {0, CS30_SW2, CS29_SW2, CS28_SW2},
    {0, CS30_SW3, CS29_SW3, CS28_SW3},
    {0, CS30_SW4, CS29_SW4, CS28_SW4},
    {0, CS30_SW5, CS29_SW5, CS28_SW5},
    {0, CS30_SW6, CS29_SW6, CS28_SW6},
    {0, CS30_SW7, CS29_SW7, CS28_SW7},

    {0, CS12_SW1, CS11_SW1, CS10_SW1},
    {0, CS12_SW2, CS11_SW2, CS10_SW2},
    {0, CS12_SW3, CS11_SW3, CS10_SW3},
    {0, CS12_SW4, CS11_SW4, CS10_SW4},
    {0, CS12_SW5, CS11_SW5, CS10_SW5},
    {0, CS12_SW6, CS11_SW6, CS10_SW6},
    {0, CS12_SW7, CS11_SW7, CS10_SW7},
    {0, CS12_SW8, CS11_SW8, CS10_SW8},
    {0, CS33_SW1, CS32_SW1, CS31_SW1},
    {0, CS33_SW2, CS32_SW2, CS31_SW2},
    {0, CS33_SW3, CS32_SW3, CS31_SW3},
    {0, CS33_SW4, CS32_SW4, CS31_SW4},
    {0, CS33_SW5, CS32_SW5, CS31_SW5},
    {0, CS33_SW7, CS32_SW7, CS31_SW7},

    {0, CS9_SW1,  CS8_SW1,  CS7_SW1 },
    {0, CS9_SW2,  CS8_SW2,  CS7_SW2 },
    {0, CS9_SW3,  CS8_SW3,  CS7_SW3 },
    {0, CS9_SW4,  CS8_SW4,  CS7_SW4 },
    {0, CS9_SW5,  CS8_SW5,  CS7_SW5 },
    {0, CS9_SW6,  CS8_SW6,  CS7_SW6 },
    {0, CS9_SW7,  CS8_SW7,  CS7_SW7 },
    {0, CS9_SW8,  CS8_SW8,  CS7_SW8 },
    {0, CS36_SW1, CS35_SW1, CS34_SW1},
    {0, CS36_SW2, CS35_SW2, CS34_SW2},
    {0, CS36_SW3, CS35_SW3, CS34_SW3},
    {0, CS36_SW4, CS35_SW4, CS34_SW4},
    {0, CS36_SW5, CS35_SW5, CS34_SW5},
    {0, CS36_SW7, CS35_SW7, CS34_SW7},

    {0, CS3_SW1,  CS2_SW1,  CS1_SW1 },
    {0, CS3_SW2,  CS2_SW2,  CS1_SW2 },
    {0, CS3_SW3,  CS2_SW3,  CS1_SW3 },
    {0, CS3_SW6,  CS2_SW6,  CS1_SW6 },
    {0, CS39_SW2, CS38_SW2, CS37_SW2},
    {0, CS39_SW3, CS38_SW3, CS37_SW3},
    {0, CS39_SW4, CS38_SW4, CS37_SW4},
    {0, CS39_SW5, CS38_SW5, CS37_SW5},
    {0, CS39_SW7, CS38_SW7, CS37_SW7}
};

#endif

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

#ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define INDICATOR_MAX_BRIGHTNESS (RGB_MATRIX_MAXIMUM_BRIGHTNESS)
#else
    #define INDICATOR_MAX_BRIGHTNESS 0xFF
#endif

#ifdef RGB_MATRIX_VAL_STEP
    #define INDICATOR_VAL_STEP (RGB_MATRIX_VAL_STEP)
#else
    #define INDICATOR_VAL_STEP 8
#endif

extern void rgb_matrix_update_pwm_buffers(void);

uint8_t light_brightness_get(void) {
    uint8_t value = rgb_matrix_get_val();
    if (value < INDICATOR_VAL_STEP) {
        value = INDICATOR_VAL_STEP;
    } else if (value < (INDICATOR_MAX_BRIGHTNESS - INDICATOR_VAL_STEP)) {
        value += INDICATOR_VAL_STEP; // one step more than current brightness
    } else {
        value = INDICATOR_MAX_BRIGHTNESS;
    }
    return value;
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { return false; }

    if (host_keyboard_led_state().caps_lock) {
        uint8_t b = light_brightness_get();
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, b, b, b);
    }
    return true;
}

void shutdown_user(void) {
    uint8_t v = light_brightness_get();
    rgb_matrix_set_color_all(v, 0, 0);
    rgb_matrix_update_pwm_buffers();
}

#endif
