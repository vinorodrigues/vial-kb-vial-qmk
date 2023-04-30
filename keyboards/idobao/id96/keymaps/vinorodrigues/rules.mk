# QMK
VIA_ENABLE = yes
LTO_ENABLE = yes
DEBOUNCE_TYPE = asym_eager_defer_pk
RGBLIGHT_ENABLE = no
NKRO_ENABLE = no
APPLE_FN_ENABLE = yes

# Vial
VIAL_ENABLE = yes
QMK_SETTINGS = no
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no

# Compiler
VPATH += keyboards/idobao/common
SRC += idobao_common.c
