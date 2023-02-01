# Copyright 2022 Vino Rodrigues (@vinorodrigues)
# SPDX-License-Identifier: GPL-3.0-or-later

VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
ENCODER_MAP_ENABLE = yes

EEPROM_DRIVER = i2c
OPT_DEFS += -DEXTERNAL_EEPROM_ENABLE

SRC += keychron_common.c
SRC += keychron_factory_test_common.c
SRC += vinorodrigues_common.c
SRC += caffeine.c
OPT_DEFS += -DFACTORY_RESET_ENABLE

DEBOUNCE_TYPE = sym_eager_pk
