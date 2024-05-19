
#ifndef V8_ENABLE
  SRC += y-muller.c
#endif

SRC += overrides.c

SRC += tri_layer.c

#ifdef ENCODER_ENABLE
  //SRC += encoder.c
#endif

SRC += tap_dance.c

#ifdef LEADER_ENABLE
  SRC += leader_key.c
#endif

#ifdef RGB_MATRIX_ENABLE
  SRC += rgb.c
#endif


SRC += features/achordion.c
