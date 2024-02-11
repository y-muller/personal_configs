
SRC += y-muller.c

SRC += overrides.c

SRC += tri_layer.c

SRC += encoder.c

SRC += tap_dance.c

ifdef ALICE69_RGB_ENABLE
  SRC += rgb_alice69.c
endif
