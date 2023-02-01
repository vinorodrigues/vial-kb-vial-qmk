VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
ENCODER_MAP_ENABLE = yes

SRC += keychron_common.c
SRC += keychron_factory_test_common.c
OPT_DEFS += -DFACTORY_RESET_ENABLE
