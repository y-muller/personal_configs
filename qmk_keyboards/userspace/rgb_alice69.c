
#include QMK_KEYBOARD_H

#include "rgb_map_alice69.h"
#include "layers.h"

extern bool alt_encoder_mode;
extern bool macro_recording_mode;

uint8_t one_shot_active_mods = 0;
uint8_t indicator_brightness = 255;

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

    if (get_highest_layer(layer_state) == 0) { // default layer
        if (alt_encoder_mode) {
            indicator_set_color(LED_DEL, HSV_ORANGE);
            indicator_set_color(LED_HOME, HSV_ORANGE);
        }
    }
    // EXTEND layer
    else if (get_highest_layer(layer_state) == EXTEND) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_UNEI); i++) {
            indicator_set_color(LED_LIST_UNEI[i], HSV_GREEN);
        }
        indicator_set_color(LED_L, HSV_ORANGE); // Home, End, PgUp, PgDn
        indicator_set_color(LED_Y, HSV_ORANGE);
        indicator_set_color(LED_J, HSV_ORANGE);
        indicator_set_color(LED_M, HSV_ORANGE);
        indicator_set_color(LED_A, HSV_CYAN);   // Mods on home row
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
        indicator_set_color(LED_DEL, HSV_RED);
        indicator_set_color(LED_HOME, HSV_ORANGE);
        indicator_set_color(LED_BSPC, HSV_GREEN);
        if (get_mods() & MOD_BIT(KC_LSFT)) {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                indicator_set_color(LED_LIST_MODS[i], HSV_RED);
            }
        }
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
    }

    return false;
}

void oneshot_mods_changed_user(uint8_t mods) {
    one_shot_active_mods = mods;
}

