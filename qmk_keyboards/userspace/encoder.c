
#ifndef ENCODER_MAP_ENABLE

#include QMK_KEYBOARD_H
#include "layers.h"

// for RGB saturation control
#include "process_rgb.h"

extern bool alt_encoder_mode;
extern uint8_t indicator_brightness;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (get_highest_layer(layer_state) == 0) { // default layer
            if (alt_encoder_mode) {
                if (clockwise) {
                   tap_code( KC_WH_D );
                } else {
                   tap_code( KC_WH_U );
                }
            } else {
                uint8_t mod_ctrl = get_mods() & MOD_MASK_CTRL;
                uint8_t osm_ctrl = get_oneshot_mods() & MOD_MASK_CTRL;
                if (mod_ctrl || osm_ctrl ) {
                    del_mods(MOD_MASK_CTRL);
                    if (clockwise) {
                        tap_code( KC_RIGHT );
                    } else {
                        tap_code( KC_LEFT );
                    }
                    if (mod_ctrl) {
                        add_mods(mod_ctrl);
                    }
                } else {
                    add_mods(MOD_MASK_CTRL);
                    if (clockwise) {
                        tap_code( KC_RIGHT );
                    } else {
                        tap_code( KC_LEFT );
                    }
                    // unregister_mods rather than del_mods so the laptop keyboard is not stuck with Ctrl
                    unregister_mods(MOD_MASK_CTRL);
                }
            }
        }
        // EXTEND layer
        else if (get_highest_layer(layer_state) == EXTEND) {
            if (clockwise) {
                tap_code( KC_VOLU );
            } else {
                tap_code( KC_VOLD );
            }
        }
        // NAV layer
        else if (get_highest_layer(layer_state) == NAV) {
            if (clockwise) {
                tap_code( KC_BRIU );
            } else {
                tap_code( KC_BRID );
            }
        }
        // NUMPAD layer
        else if (get_highest_layer(layer_state) == NUMPAD) {
            if (clockwise) {
                tap_code( KC_WH_D );
            } else {
                tap_code( KC_WH_U );
            }
        }
        // SYSTEM layer
        else if (get_highest_layer(layer_state) == SYSTEM) {
            if (get_mods() & MOD_BIT(KC_LSFT)) {
                if (clockwise) {
                    indicator_brightness = (indicator_brightness+16 <= 255) ? indicator_brightness+16 : 255;
                } else {
                    indicator_brightness = (indicator_brightness >= 16) ? indicator_brightness-16 : 0;
                }
            } else {
                // create a fake key record to process the RGB value
                keyrecord_t record;
                record.event.pressed = false;
                if (clockwise) {
                    process_rgb( RGB_VAI, &record );
                } else {
                    process_rgb( RGB_VAD, &record );
                }
            }
        }
#ifdef AZERTY_LAYER_ENABLE
        // AZ_SYM layer
        else if (get_highest_layer(layer_state) == AZ_SYM) {
            if (clockwise) {
                tap_code( KC_VOLU );
            } else {
                tap_code( KC_VOLD );
            }
        }
#endif  // AZERTY_LAYER_ENABLE
    }
    return false;
}

#endif // ndef ENCODER_MAP_ENABLE
