# Copyright 2022 Vino Rodrigues (@vinorodrigues)
# SPDX-License-Identifier: GPL-3.0-or-later

VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
ENCODER_MAP_ENABLE = yes

NKRO_ENABLE = no
APPLE_FN_ENABLE = yes

EEPROM_DRIVER = i2c
OPT_DEFS += -DEXTERNAL_EEPROM_ENABLE
OPT_DEFS += -DFACTORY_RESET_ENABLE

DEBOUNCE_TYPE = asym_eager_defer_pk

SRC += keychron_common.c keychron_ft_common.c
SRC += vinorodrigues_common.c caffeine.c dice.c
