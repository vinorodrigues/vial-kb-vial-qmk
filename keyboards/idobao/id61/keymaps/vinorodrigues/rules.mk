# QMK
VIA_ENABLE = yes
LTO_ENABLE = yes
NKRO_ENABLE = no  # N-Key Rollover must be OFF for mac keys to work
APPLE_FN_ENABLE = yes

# vial
VIAL_ENABLE = yes
QMK_SETTINGS = no
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no

# Compiler
VPATH += keyboards/idobao/common
SRC += idobao_common.c id61_common.c
