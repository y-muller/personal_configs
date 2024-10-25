/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define EE_HANDS

// Single encoder on the right half
#define ENCODER_MAP_ENABLE
#undef ENCODER_A_PINS
#undef ENCODER_B_PINS
#undef ENCODER_A_PINS_RIGHT
#undef ENCODER_B_PINS_RIGHT
#define ENCODERS_PAD_A { }
#define ENCODERS_PAD_B { }
#define ENCODER_RESOLUTIONS { }
#define ENCODERS_PAD_A_RIGHT { GP24 }
#define ENCODERS_PAD_B_RIGHT { GP7 }
#define ENCODER_RESOLUTIONS_RIGHT { 4 }
#define ENCODER_DIRECTION_FLIP

//#define QUICK_TAP_TERM 0
//#define TAPPING_TERM 100

#if defined(DYNAMIC_KEYMAP_LAYER_COUNT)
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 16

#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

// Add a delay to solve issues with modifiers in macros
#define TAP_CODE_DELAY 5

#define ONESHOT_TIMEOUT 2000

// Tap dance, mod-tap config
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY
#define RETRO_TAPPING
#define RETRO_TAPPING_PER_KEY
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL

// Leader key config
#define LEADER_TIMEOUT 450
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT
//#define LEADER_KEY_STRICT_KEY_PROCESSING

// Combos are defined on the default layer
//#define COMBO_ONLY_FROM_LAYER 0

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// Mouse mode Combined: accelerated + speed button
#define MK_COMBINED
#define MOUSEKEY_MAX_SPEED 6

// userspace config
#define ORTHO_FEATURES
#define CORNE_FEATURES
#define CORNE_46KEYS
#define AZERTY_LAYER_ENABLE
#define ACHORDION_ENABLE
#define ACHORDION_STREAK
#define LAYERLOCK_ENABLE
#define BASE_LAYER_TOP 0 // This board only uses the first layer (no Mac/Win switch)
#define SYSTEM_LAYER_COMBO

#define SPLIT_TRANSACTION_IDS_USER                                                                                 \
        RPC_ID_USER_RUNTIME_STATE_SYNC, RPC_ID_USER_KEYMAP_SYNC, RPC_ID_USER_CONFIG_SYNC, RPC_ID_USER_AUTOCORRECT_STR, \
            RPC_ID_USER_DISPLAY_KEYLOG_STR, RPC_ID_USER_SUSPEND_STATE_SYNC
