# QMK
VIA_ENABLE = yes
LTO_ENABLE = yes
NKRO_ENABLE = no

# Vial
VIAL_ENABLE = yes
QMK_SETTINGS = no
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no

# Compiler
VPATH += keyboards/idobao/common
SRC += id27_common.c idobao_common.c
