// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x3A, 0x4A, 0xE7, 0x57, 0xC9, 0xF3, 0xF8, 0xB5}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

#ifdef RGB_MATRIX_ENABLE
    #define ID67_DISABLE_UNDERGLOW

    #undef ENABLE_RGB_MATRIX_PIXEL_RAIN
    #undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#endif
