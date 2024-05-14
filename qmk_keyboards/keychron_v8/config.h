
#if defined(DYNAMIC_KEYMAP_LAYER_COUNT)
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

#if defined(CAPS_LOCK_LED_INDEX)
    #undef CAPS_LOCK_LED_INDEX
#endif

// Add a delay to solve issues with modifiers in macros
#define TAP_CODE_DELAY 5

#define ONESHOT_TIMEOUT 2000

// Tap dance config
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Leader key config
#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// Mouse mode Combined: accelerated + speed button
#define MK_COMBINED
#define MOUSEKEY_MAX_SPEED 6

// userspace config
#define BASE_LAYER_TOP 0 // This board only uses the first layer (ignore Mac/Win switch)
#define MACRO_ANSI_69    // macro name is inverted

// the encoder of the V8 is inverted
#define ENCODER_DIRECTION_FLIP

