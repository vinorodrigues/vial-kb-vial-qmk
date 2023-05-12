// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0xD5, 0xAA, 0x58, 0xFA, 0xD7, 0xB0, 0xD2, 0x00}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 12 }

/* Make Caps-Lock Tap/Hold Faster */
#undef TAPPING_TERM
#define TAPPING_TERM 100

#define ID61_DISABLE_UNDERGLOW  // All ID61's don't have visible underside
