
SRC += y-muller.c

SRC += overrides.c

SRC += tri_layer.c

#ifdef ENCODER_ENABLE
  SRC += encoder.c
#endif

SRC += tap_dance.c

#ifdef LEADER_ENABLE
  SRC += leader_key.c
#endif

#ifdef RGB_MATRIX_ENABLE
  SRC += rgb.c
#endif

#ifdef ACHORDION_ENABLE
  SRC += features/achordion.c
#endif
