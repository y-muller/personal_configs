
#include QMK_KEYBOARD_H

#include "keymap_french.h"

#include "layers.h"
#include "custom_keys.h"
#include "tap_dance.h"

HSV prev_hsv;
int prev_rgb_mode;

bool alt_encoder_mode = false;
bool macro_recording_mode = false;

extern bool tmux_lock;

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (tmux_lock) {
        // While TMUX is locked on, send C(A) before all other keys
        if (record->event.pressed) {
            register_code( KC_LCTL );
            wait_ms(10);
            tap_code( KC_A );
            wait_ms(10);
            unregister_code( KC_LCTL );
            wait_ms(10);
        }
    }

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

        // Toggle the encoder mode
        case CC_EMTG:
            if (record->event.pressed) {
                alt_encoder_mode = !alt_encoder_mode;
            }
            return false;

// only if using ENCODER_MAP, otherwise handled in encoder.c
#if defined(ENCODER_MAP_ENABLE)
        case CC_ECCW:
            if (alt_encoder_mode) {
                if (record->event.pressed) {
                    tap_code( KC_WH_U );
                }
            } else {
                if (record->event.pressed) {
                    tap_code( KC_LEFT );
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
                    tap_code( KC_RIGHT );
                }
            }
            return false;
#endif

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

void leader_start_user(void) {
    print("leader_start_user\n");
}

void leader_end_user(void) {
    print("leader_end_user\n");
    if (leader_sequence_one_key( TD_TMUX )) {
        // cancel leader sequence
    } else if (leader_sequence_one_key(KC_COMM)) {
        register_code( KC_LSFT );
        wait_ms(10);
        tap_code( KC_COMM );
        tap_code( KC_DOT );
        wait_ms(10);
        unregister_code( KC_LSFT );
        wait_ms(10);
        tap_code( KC_LEFT );
    } else if (leader_sequence_one_key(KC_DOT)) {
        register_code( KC_LSFT );
        wait_ms(10);
        tap_code( KC_COMM );
        wait_ms(10);
        unregister_code( KC_LSFT );
        wait_ms(10);
        tap_code( KC_SLSH );
        wait_ms(10);
        register_code( KC_LSFT );
        wait_ms(10);
        tap_code( KC_DOT );
        wait_ms(10);
        unregister_code( KC_LSFT );
        wait_ms(10);
        tap_code( KC_LEFT );
    }
}

void dynamic_macro_record_start_user(void) {
    macro_recording_mode = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    macro_recording_mode = false;
}

void keyboard_post_init_user(void) {
#ifdef USER_CONFIG_ENABLE
    user_config_init();
#endif  // USER_CONFIG_ENABLE

#ifdef BLUETOOTH_POST_INIT
    if (get_transport() == TRANSPORT_BLUETOOTH) {
        prev_hsv = rgb_matrix_get_hsv();
        prev_rgb_mode = rgb_matrix_get_mode();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
    }
#endif  // BLUETOOTH_POST_INIT
}