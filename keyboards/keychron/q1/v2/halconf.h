// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_I2C TRUE
#ifdef ENCODER_ENABLE
#    define PAL_USE_CALLBACKS TRUE
#endif

#include_next <halconf.h>
