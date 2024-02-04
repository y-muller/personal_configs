
#include QMK_KEYBOARD_H

#include "keymap_french.h"

#include "layers.h"
#include "custom_keys.h"

HSV prev_hsv;
int prev_rgb_mode;

bool alt_encoder_mode = false;

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CC_ELOCK:
            if (record->event.pressed) {
                if (is_oneshot_layer_active()) {
                    reset_oneshot_layer();
                    layer_on(EXTEND);
                } else {
                    layer_off(EXTEND);
                }
            }
            return false;

        case CC_EMTG:
            if (record->event.pressed) {
                alt_encoder_mode = !alt_encoder_mode;
            }
            return false;

        case CC_ECCW:
            if (alt_encoder_mode) {
                if (record->event.pressed) {
                    tap_code( KC_WH_U );
                }
            } else {
                if (record->event.pressed) {
                    mod_state = get_mods();
                    if (mod_state & MOD_MASK_CTRL) {
                        del_mods(MOD_MASK_CTRL);
                    } else {
                        add_mods(MOD_MASK_CTRL);
                    }
                    register_code( KC_LEFT );
                    set_mods(mod_state);
                } else {
                    unregister_code( KC_LEFT );
                }
            }
            return false;

        case CC_ECW:
            if (alt_encoder_mode) {
                if (record->event.pressed) {
                    tap_code( KC_WH_D );
                }
            } else {
                if (record->event.pressed) {
                    mod_state = get_mods();
                    if (mod_state & MOD_MASK_CTRL) {
                        del_mods(MOD_MASK_CTRL);
                    } else {
                        add_mods(MOD_MASK_CTRL);
                    }
                    register_code( KC_RIGHT );
                    set_mods(mod_state);
                } else {
                    unregister_code( KC_RIGHT );
                }
            }
            return false;

        case CC_SRCN:
            mod_state = get_mods();
            if (mod_state & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code( KC_F8 );
                    set_mods(mod_state);
                } else {
                    unregister_code( KC_F8 );
                }
            } else {
                if (record->event.pressed) {
                    register_code( KC_F3 );
                } else {
                    unregister_code( KC_F3 );
                }
            }
            return false;

        case CC_SRCP:
            mod_state = get_mods();
            if (mod_state & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    del_mods(MOD_MASK_SHIFT);
                    add_mods(MOD_MASK_CTRL);
                    register_code( KC_F8 );
                    set_mods(mod_state);
                } else {
                    unregister_code( KC_F8 );
                }
            } else {
                if (record->event.pressed) {
                    register_code16( S(KC_F3) );
                } else {
                    unregister_code16( S(KC_F3) );
                }
            }
            return false;

        case CC_RGBTG:
            // toggle RGB between indicators only and a previous value
            if (record->event.pressed) {
                if( rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
                    rgb_matrix_mode_noeeprom(prev_rgb_mode);
                    rgb_matrix_sethsv_noeeprom(prev_hsv.h,prev_hsv.s,prev_hsv.v);
                } else {
                    // set indicators only (solid black)
                    prev_hsv = rgb_matrix_get_hsv();
                    prev_rgb_mode = rgb_matrix_get_mode();
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                }
            }
            return true;

        case CC_RGBRT:
            // set RGB to defaults
            if (record->event.pressed) {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                rgb_matrix_sethsv_noeeprom(255,255,255);
            }
            return true;

        case CC_DISP: // handle the display switch key on Thinhpad (F7)
            if (record->event.pressed) {
                host_system_send( SYSTEM_DISPLAY_TOGGLE_INT_EXT );
            } else {
                host_system_send( 0 );
            }
            return false; // Skip all further processing of this key

        default:
            return true; // Process all other keycodes normally
    }
}

#ifdef BLUETOOTH_POST_INIT
void keyboard_post_init_user(void) {
    if (get_transport() == TRANSPORT_BLUETOOTH) {
        prev_hsv = rgb_matrix_get_hsv();
        prev_rgb_mode = rgb_matrix_get_mode();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
    }
}
#endif