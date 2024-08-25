
#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE

#ifdef CORNE_FEATURES
#    include "layers_corne.h"
#    ifdef CORNE_46KEYS
#        include "rgb_map_corne46.h"
#    else
#        include "rgb_map_corne.h"
#    endif
// ...
#else
#    ifdef ORTHO_FEATURES
#        include "rgb_map_ortho47.h"
#        include "layers_ortho47.h"
#    else
#        include "rgb_map_alice69.h"
#        include "layers_alice69.h"
#    endif
#endif

extern bool alt_encoder_mode;
extern bool macro_recording_mode;
extern bool tmux_lock;

uint8_t one_shot_active_mods = 0;
uint8_t indicator_brightness = 120;

// lights up a key as indicator - input is in HSV
// brightness is adjusted according to config and colour is converted to RGB
void indicator_set_color(uint8_t led_pos, uint8_t h, uint8_t s, uint8_t v)
{
    HSV indhsv;
    indhsv.h = h;
    indhsv.s = s;
    indhsv.v = indicator_brightness;
    RGB indrgb = hsv_to_rgb(indhsv);
    rgb_matrix_set_color(led_pos, indrgb.r, indrgb.g, indrgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (macro_recording_mode) {
         for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            indicator_set_color(i, HSV_PINK);
        }
    }
    else if (leader_sequence_active()) {
        //for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        //    indicator_set_color(i, HSV_WHITE);
        //}
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            indicator_set_color(LED_LIST_MODS[i], HSV_WHITE);
        }
    }
    else if (tmux_lock) {
         for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            indicator_set_color(i, HSV_ORANGE);
        }
    }
    // Turn off RGB on undefined layer keys
    else if (get_highest_layer(layer_state) > BASE_LAYER_TOP) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) <= KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_BLACK);
                }
            }
        }
    }

    #ifdef ENCODER_ENABLE
    if (get_highest_layer(layer_state) == 0) { // default layer
        if (alt_encoder_mode) {
#           ifdef CORNE_FEATURES
            indicator_set_color(LED_Q, HSV_ORANGE);
            indicator_set_color(LED_W, HSV_ORANGE);
#           else
            indicator_set_color(LED_DEL, HSV_ORANGE);
            indicator_set_color(LED_HOME, HSV_ORANGE);
#           endif
        }
    } else
    #endif
    // EXTEND layer
    if (get_highest_layer(layer_state) == EXTEND) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_UNEI); i++) {
            indicator_set_color(LED_LIST_UNEI[i], HSV_GREEN);
        }
        indicator_set_color(LED_L, HSV_ORANGE); // Home, End, PgUp, PgDn
        indicator_set_color(LED_Y, HSV_ORANGE);
        indicator_set_color(LED_J, HSV_ORANGE);
        indicator_set_color(LED_M, HSV_ORANGE);
        indicator_set_color(LED_A, HSV_CYAN);  // Mods on home row 
        indicator_set_color(LED_R, HSV_CYAN);
        indicator_set_color(LED_S, HSV_CYAN);
        indicator_set_color(LED_T, HSV_CYAN);
        indicator_set_color(LED_SCLN, HSV_RED); // Delete
        indicator_set_color(LED_O, HSV_RED);    // Backspace
        indicator_set_color(LED_SLSH, HSV_RED); // Delete previous word
    }
    // NAV layer
    else if (get_highest_layer(layer_state) == NAV) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NEIO); i++) {
            indicator_set_color(LED_LIST_NEIO[i], HSV_BLUE);
        }
    }
    #ifdef ORTHO_FEATURES
    else if (get_highest_layer(layer_state) == MEDIA) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_UNEI); i++) {
            indicator_set_color(LED_LIST_UNEI[i], HSV_ORANGE);
        }
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_ARROWS); i++) {
            indicator_set_color(LED_LIST_ARROWS[i], HSV_GREEN);
        }
        indicator_set_color(LED_Q, HSV_CYAN);      // Volume and brightness
        indicator_set_color(LED_W, HSV_CYAN);
        indicator_set_color(LED_F, HSV_CYAN);
        indicator_set_color(LED_R, HSV_CYAN);
        indicator_set_color(LED_S, HSV_CYAN);
        indicator_set_color(LED_J, HSV_WHITE);    // LLock
        indicator_set_color(LED_TAB, HSV_WHITE);  // LLock
    }
    #endif
    else if (get_highest_layer(layer_state) == NUMPAD) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD); i++) {
            indicator_set_color(LED_LIST_NUMPAD[i], HSV_BLUE);
        }
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NUMPAD_SYM); i++) {
            indicator_set_color(LED_LIST_NUMPAD_SYM[i], HSV_ORANGE);
        }
        if ( ! host_keyboard_led_state().num_lock) {
            indicator_set_color(LED_Z, HSV_RED);
        }
    }
    else if (get_highest_layer(layer_state) == SYSTEM) {
        indicator_set_color(_LED_BOOT, HSV_RED);
        indicator_set_color(_LED_DEBUG, HSV_ORANGE);
        indicator_set_color(_LED_RSTP, HSV_YELLOW);
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_RGB_SETTINGS); i++) {
            indicator_set_color(LED_LIST_RGB_SETTINGS[i], HSV_GOLDENROD);
        }
        #ifdef ORTHO_FEATURES
        indicator_set_color(LED_TAB, HSV_TURQUOISE); // Base maps
        indicator_set_color(LED_Q, HSV_TURQUOISE);
        indicator_set_color(LED_W, HSV_TURQUOISE);
        indicator_set_color(LED_J, HSV_SPRINGGREEN); // Dyn Macro
        indicator_set_color(LED_M, HSV_GREEN);
        indicator_set_color(LED_K, HSV_RED);  // Suspend
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_FUNC); i++) {
            indicator_set_color(LED_LIST_FUNC[i], HSV_YELLOW);
        }
        #else
        indicator_set_color(LED_MINS, HSV_GREEN); // Dyn Macros
        indicator_set_color(LED_EQUL, HSV_GREEN);
        indicator_set_color(LED_BSPC, HSV_SPRINGGREEN);
        #endif
    }

    // Caps lock - turn all the modifier red
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            indicator_set_color(LED_LIST_MODS[i], HSV_RED);
        }
    }
    else if (is_caps_word_on()) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            indicator_set_color(LED_LIST_MODS[i], HSV_GREEN);
        }
    }

    if (leader_sequence_active()) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                indicator_set_color(i, HSV_BLUE);
            }
        }
    }

    if (one_shot_active_mods!=0)
    {
        if (one_shot_active_mods & MOD_MASK_SHIFT)
        {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                indicator_set_color(LED_LIST_MODS[i], HSV_YELLOW);
            }
        }
        else if (one_shot_active_mods & MOD_MASK_CTRL)
        {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                indicator_set_color(LED_LIST_MODS[i], HSV_ORANGE);
            }
        }
        else if (one_shot_active_mods & MOD_BIT(KC_RALT))
        {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                indicator_set_color(LED_LIST_MODS[i], HSV_CYAN);
            }
        }
    }

    return false;
}

void oneshot_mods_changed_user(uint8_t mods) {
    one_shot_active_mods = mods;
}

#endif