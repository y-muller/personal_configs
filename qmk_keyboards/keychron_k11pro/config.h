
#if defined(DYNAMIC_KEYMAP_LAYER_COUNT)
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 7

#if defined(CAPS_LOCK_INDEX)
    #undef CAPS_LOCK_INDEX
#endif

#undef ENCODER_MAP_ENABLE

#define ONESHOT_TIMEOUT 2000

// Mouse mode Combined: accelerated + speed button
#define MK_COMBINED
#define MOUSEKEY_MAX_SPEED 6

// userspace config
#define BASE_LAYER_TOP 1 // This board uses two base layers Mac=AZERTY, Win=COLEMAK
#define AZERTY_LAYER_ENABLE
#define BLUETOOTH_KEY_CONTROL
