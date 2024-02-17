
#if defined(DYNAMIC_KEYMAP_LAYER_COUNT)
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 7

#if defined(CAPS_LOCK_INDEX)
    #undef CAPS_LOCK_INDEX
#endif

#define TAP_CODE_DELAY 5

#define ONESHOT_TIMEOUT 2000

// Tap dance config
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY

// Leader key config
#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT

// Mouse mode Combined: accelerated + speed button
#define MK_COMBINED
#define MOUSEKEY_MAX_SPEED 6

// encoder is handled in encoder_update_user
#undef ENCODER_MAP_ENABLE

// userspace config
#define BASE_LAYER_TOP 1 // This board uses two base layers Mac=AZERTY, Win=COLEMAK
#define AZERTY_LAYER_ENABLE
#define BLUETOOTH_KEY_CONTROL
