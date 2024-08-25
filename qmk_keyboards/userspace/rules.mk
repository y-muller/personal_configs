
SRC += tap_dance.c

SRC += y-muller.c

SRC += overrides.c

ifeq ($(CUSTOM_TRI_LAYER), yes)
    SRC += tri_layer.c
endif

#ifdef ENCODER_ENABLE
  SRC += encoder.c
#endif

#ifdef LEADER_ENABLE
  SRC += leader_key.c
#endif

#ifdef RGB_MATRIX_ENABLE
  SRC += rgb.c
#endif

#ifeq ACHORDION_ENABLE
  SRC += features/achordion.c
#endif

SRC += features/layer_lock.c