
#include QMK_KEYBOARD_H

#include "rgb_map_alice69.h"
#include "layers.h"

uint8_t one_shot_active_mods = 0;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    // Turn off RGB on undefined layer keys
    if (get_highest_layer(layer_state) > BASE_LAYER_TOP) {
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

    // EXTEND layer
    if (get_highest_layer(layer_state) == EXTEND) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_UNEI); i++) {
            rgb_matrix_set_color(LED_LIST_UNEI[i], RGB_GREEN);
        }
        rgb_matrix_set_color(LED_L, RGB_ORANGE); // Home, End, PgUp, PgDn
        rgb_matrix_set_color(LED_Y, RGB_ORANGE);
        rgb_matrix_set_color(LED_J, RGB_ORANGE);
        rgb_matrix_set_color(LED_M, RGB_ORANGE);
        rgb_matrix_set_color(LED_A, RGB_CYAN);   // Mods on home row
        rgb_matrix_set_color(LED_S, RGB_CYAN);
        rgb_matrix_set_color(LED_T, RGB_CYAN);
        rgb_matrix_set_color(LED_SCLN, RGB_RED); // Delete
        rgb_matrix_set_color(LED_O, RGB_RED);    // Backspace
    }
    // NAV layer
    else if (get_highest_layer(layer_state) == NAV) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_NEIO); i++) {
            rgb_matrix_set_color(LED_LIST_NEIO[i], RGB_BLUE);
        }
    }

    // Caps lock - turn all the modifier red
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            rgb_matrix_set_color(LED_LIST_MODS[i], RGB_RED);
        }
    }
    else if (is_caps_word_on()) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            rgb_matrix_set_color(LED_LIST_MODS[i], RGB_GREEN);
        }
    }

    if (leader_sequence_active()) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_BLUE);
            }
        }
    }

    if (one_shot_active_mods!=0)
    {
        if (one_shot_active_mods & MOD_MASK_SHIFT)
        {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], RGB_YELLOW);
            }
        }
        else if (one_shot_active_mods & MOD_MASK_CTRL)
        {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], RGB_ORANGE);
            }
        }
    }

    return false;
}

void oneshot_mods_changed_user(uint8_t mods) {
    one_shot_active_mods = mods;
}

