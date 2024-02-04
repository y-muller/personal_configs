
#if defined(DYNAMIC_KEYMAP_LAYER_COUNT)
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#if defined(CAPS_LOCK_LED_INDEX)
    #undef CAPS_LOCK_LED_INDEX
#endif

#define ONESHOT_TIMEOUT 2000

// Mouse mode Combined: accelerated + speed button
#define MK_COMBINED
#define MOUSEKEY_MAX_SPEED 6

// the encoder of the V8 is inverted
#define ENCODER_DIRECTION_FLIP

// encoder is handled in encoder_update_user
#undef ENCODER_MAP_ENABLE

// userspace config
#define BASE_LAYER_TOP 0 // This board only uses the first layer (ignore Mac/Win switch)
#define MACRO_ANSI_69    // macro name is inverted
