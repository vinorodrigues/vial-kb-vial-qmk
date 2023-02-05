// Copyright 2023 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include "color.h"

RGB to_rgb(uint8_t r, uint8_t g, uint8_t b);
HSV to_hsv(uint8_t h, uint8_t s, uint8_t v);
HSV rgb_to_hsv(RGB rgb);
