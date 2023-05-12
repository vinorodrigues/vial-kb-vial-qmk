# The ID67 Besttype case has a sealed/solid undercase,
#  this enables switching off thoes LEDs
# Usage:  `make idobao/id67:default UNDERGLOW=off`

UNDERGLOW ?= yes
ifneq ($(strip $(UNDERGLOW)), yes)
  OPT_DEFS += -DID67_DISABLE_UNDERGLOW
endif
