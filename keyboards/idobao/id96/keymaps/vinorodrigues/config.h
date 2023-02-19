// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x8E, 0x15, 0xBB, 0xE7, 0x05, 0x11, 0xD1, 0x21}
#define VIAL_UNLOCK_COMBO_ROWS { 5, 9 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

#define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x94
