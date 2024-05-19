
#include QMK_KEYBOARD_H

#ifdef AZERTY_LAYER_ENABLE
#include "keymap_french.h"
#endif

#ifdef ORTHO_FEATURES
#include "layers_ortho47.h"
#else
#include "layers_alice69.h"
#endif

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif

#include "custom_keys.h"
#include "tap_dance.h"

HSV prev_hsv;
int prev_rgb_mode;

bool alt_encoder_mode = false;
bool macro_recording_mode = false;
#ifdef AZERTY_LAYER_ENABLE
bool french_layer_active = false;
#endif

extern bool tmux_lock;

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) { return false; }
#endif

    if (tmux_lock) {
        // While TMUX is locked on, send C(A) before all other keys
        if (record->event.pressed) {
            tap_code16( C(KC_A) );
        }
    }

    switch (keycode) {
#ifdef ORTHO_FEATURES
        case TAB_MS:
            if (!record->tap.count && record->event.pressed) {
                // Intercept hold function to enable OSM layer
                set_oneshot_layer(MEDIA, ONESHOT_START);
                return false;
            } else if (!record->tap.count && !record->event.pressed) {
                // hold release ?
                clear_oneshot_layer_state(ONESHOT_PRESSED);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case C_MEDIA:
            if (record->event.pressed) {
                layer_invert(MEDIA);
            }
            return false;
#endif

        case C_CLMK1:
            set_single_persistent_default_layer(COLEMAK);
            #ifdef AZERTY_LAYER_ENABLE
            layer_off( FRENCH );
            french_layer_active = false;
            #endif
            return false;

        case C_CLMK2:
            set_single_persistent_default_layer(COLEMAKH);
            #ifdef AZERTY_LAYER_ENABLE
            layer_off( FRENCH );
            french_layer_active = false;
            #endif
            return false;

        case C_FRENCH:
            #ifdef AZERTY_LAYER_ENABLE
            french_layer_active = true;
            layer_on( FRENCH );
            #endif
            return false;

        case C_OSLLCK:
            if (record->event.pressed) {
                int current_layer = get_highest_layer(layer_state);
                if (is_oneshot_layer_active()) {
                    reset_oneshot_layer();
                    layer_on(current_layer);
                } else {
                    layer_off(current_layer);
                }
            }
            return false;

        case C_NUMLK:
            if (record->event.pressed) {
                if (is_oneshot_layer_active()) {
                    reset_oneshot_layer();
#ifdef ORTHO_FEATURES
                    layer_on(NUMBERS);
#else
                    layer_on(NUMPAD);
#endif
                } else {
#ifdef ORTHO_FEATURES
                    layer_off(NUMBERS);
#else
                    layer_off(NUMPAD);
#endif
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

        case CC_LINE:
            // select whole line
            if (record->event.pressed) {
                tap_code( KC_HOME );
                tap_code( KC_HOME );
                tap_code16( S(KC_DOWN) );
            }
            return false;

        case CC_DOTSC:
            // Dot-Space-Shift: ends sentence and start new one
            if (record->event.pressed) {
                tap_code( KC_DOT );
                tap_code( KC_SPACE );
                set_oneshot_mods(MOD_BIT(KC_LSFT));
            }
            return false;

        case C_PLSPLS:
            // ++
            if (record->event.pressed) {
                tap_code16( KC_PLUS );
                tap_code16( KC_PLUS );
            }
            return false;

        case CC_SRCN:
            // navigate through search results - next
            // with F3 and Shift-F3 or with F8 and Ctrl-F8 if Shift is pressed
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
            // navigate through search results - previous
            // with F3 and Shift-F3 or with F8 and Ctrl-F8 if Shift is pressed
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
                if( !rgb_matrix_is_enabled() ) {
                    rgb_matrix_enable_noeeprom();
                    rgb_matrix_mode_noeeprom(prev_rgb_mode);
                    rgb_matrix_sethsv_noeeprom(prev_hsv.h,prev_hsv.s,prev_hsv.v);
                } else if( rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
                    rgb_matrix_disable_noeeprom();
                } else {
                    // set indicators only (solid black)
                    prev_hsv = rgb_matrix_get_hsv();
                    prev_rgb_mode = rgb_matrix_get_mode();
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                }
            }
            return false;

        case CC_RGBRT:
            // set RGB to defaults
            if (record->event.pressed) {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                rgb_matrix_sethsv_noeeprom(255,255,255);
            }
            return false;

        case CC_DISP: // handle the display switch key on Thinhpad (F7)
            if (record->event.pressed) {
                host_system_send( SYSTEM_DISPLAY_TOGGLE_INT_EXT );
            } else {
                host_system_send( 0 );
            }
            return false; // Skip all further processing of this key

        case LP_PIPE:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' || '
                tap_code(KC_SPC);
                tap_code16(KC_PIPE);
                tap_code16(KC_PIPE);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(KC_PIPE);
            }
            return false;

        case LP_AMPR:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' && '
                tap_code(KC_SPC);
                tap_code16(KC_AMPR);
                tap_code16(KC_AMPR);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(KC_AMPR);
            }
            return false;

        case LP_EXLM:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' != '
                tap_code(KC_SPC);
                tap_code16(KC_EXLM);
                tap_code16(KC_EQL);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(KC_EXLM);
            }
            return false;

        case LP_EQL:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' = '
                tap_code(KC_SPC);
                tap_code(KC_EQL);
                tap_code(KC_SPC);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_EQEQ:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' == '
                tap_code(KC_SPC);
                tap_code16(KC_EQL);
                tap_code16(KC_EQL);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                tap_code16(KC_EQL);
                tap_code16(KC_EQL);
            }
            return false;

        case LP_SLSH:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ~/ or ../
                mod_state = get_mods();
                uint8_t osm_state = get_oneshot_mods();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16(KC_DOT);
                    tap_code16(KC_DOT);
                    tap_code16(KC_SLSH);
                    set_mods(mod_state);
                } else {
                    tap_code16(KC_TILD);
                    tap_code16(KC_SLSH);
                }
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_SLSL:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '// '
                tap_code16(KC_SLSH);
                tap_code16(KC_SLSH);
                tap_code(KC_SPC);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode


        case LP_COLN:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_COLN); // Intercept hold function to send ::
                tap_code16(KC_COLN);
                return false;
            } else if (record->event.pressed) {
                tap_code16(KC_COLN);
            }
            return false;

        case LP_LPRN:
            //printf("  tap.count=%d, thing=%d\n", record->tap.count, record->event.interrupted);
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '()' cursor in middle
                tap_code16(KC_LPRN);
                tap_code16(KC_RPRN);
                //tap_code(KC_LEFT);
            } else if (record->event.pressed) {
                tap_code16(KC_LPRN);
            }
            return false;

        case LP_LBRC:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '[]' cursor in middle
                tap_code(KC_LBRC);
                tap_code(KC_RBRC);
                //tap_code(KC_LEFT);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_LCBR:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '{}' cursor in middle
                tap_code16(KC_LCBR);
                tap_code16(KC_RCBR);
                //tap_code(KC_LEFT);
            } else if (record->event.pressed) {
                tap_code16(KC_LCBR);
            }
            return false;

        case LP_RPRN:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ');↵'
                tap_code16(KC_RPRN);
                tap_code16(KC_SCLN);
                tap_code16(KC_ENT);
            } else if (record->event.pressed) {
                tap_code16(KC_RPRN);
            }
            return false;

        case LP_DOT:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '. ' one-shot shift
                tap_code( KC_DOT );
                tap_code( KC_SPACE );
                set_oneshot_mods(MOD_BIT(KC_LSFT));
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        default:
            return true; // Process all other keycodes normally
    }
}

void matrix_scan_user(void) {
#ifdef ACHORDION_ENABLE
    achordion_task();
#endif
}

#ifdef ACHORDION_ENABLE
bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Also allow same-hand holds when the other key is in the rows below the
  // alphas or first column.
  if (tap_hold_record->event.key.row == 3) { return true; }
  if (tap_hold_record->event.key.col == 0) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}
#endif

void dynamic_macro_record_start_user(int8_t direction) {
    macro_recording_mode = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    macro_recording_mode = false;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case K_CAPS: // Tap dance for Caps Word itself
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
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