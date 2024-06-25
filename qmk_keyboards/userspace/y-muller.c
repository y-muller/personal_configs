
#include QMK_KEYBOARD_H

#include "y-muller.h"

#include "keymap_french.h"

#ifdef CORNE_FEATURES
#include "layers_corne.h"
#elifdef ORTHO_FEATURES
#include "layers_ortho47.h"
#else
#include "layers_alice69.h"
#endif

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif

#ifdef LAYERLOCK_ENABLE
#include "features/layer_lock.h"
#endif

#include "custom_keys.h"
#include "tap_dance.h"

#ifdef RGB_MATRIX_ENABLE
HSV prev_hsv;
int prev_rgb_mode;
#endif

bool alt_encoder_mode = false;
bool macro_recording_mode = false;

extern bool tmux_lock;

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) { return false; }
#endif

#ifdef LAYERLOCK_ENABLE
    if (!process_layer_lock(keycode, record, C_LLOCK)) { return false; }
#endif

    process_tmux_mode(keycode, record);

    switch (keycode) {
#ifdef ORTHO_FEATURES
        case ESC_MD:
            if (!record->tap.count && record->event.pressed) {
                // Intercept hold function to enable OSM layer
                set_oneshot_layer(MEDIA, ONESHOT_START);
                return false;
            } else if (!record->tap.count && !record->event.pressed) {
                // hold release
                clear_oneshot_layer_state(ONESHOT_PRESSED);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case C_MEDIA:
            if (record->event.pressed) {
#ifdef LAYERLOCK_ENABLE
                layer_lock_invert(MEDIA);
#else
                layer_invert(MEDIA);
#endif
            }
            return false;
#endif

        case C_CLMK1:
            set_single_persistent_default_layer(COLEMAK);
            return false;

        case C_CLMK2:
            set_single_persistent_default_layer(COLEMAKH);
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
                    layer_on(NUMPAD);
                } else {
                    layer_off(NUMPAD);
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

#ifdef RGB_MATRIX_ENABLE
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
#endif

        case CC_DISP: // handle the display switch key on Thinhpad (F7)
            if (record->event.pressed) {
                host_system_send( SYSTEM_DISPLAY_TOGGLE_INT_EXT );
            } else {
                host_system_send( 0 );
            }
            return false; // Skip all further processing of this key

        case C_TMUX: // 
            if (record->event.pressed) {
                tmux_lock = true;
            } else {
                tmux_lock = false;
            }
            return false; // Skip all further processing of this key

        case C_HELP:
            if (record->event.pressed) {
                show_layout_help();
            } else {
                close_layout_help();
            }
            return false;

        case HRM_ASTR:
            if (!record->tap.count && record->event.pressed) {
                 return true;
            } else if (record->event.pressed) {
                tap_code16( KC_ASTR );
                return false;
            }
            return true;

        case K_SYMBS:
            if (!record->tap.count && record->event.pressed) {
                 return true;
            } else if (record->event.pressed) {
                set_oneshot_mods(MOD_BIT(KC_RALT));
                return false;
            }
            return true;

        case C_OSWIN:
            if (record->event.pressed) {
                add_oneshot_mods(MOD_BIT(KC_LWIN));
                return false;
            }
            return true;

        case C_VIMCMD:
            // ESC colon
            if (record->event.pressed) {
                tap_code16( KC_ESC );
                tap_code16( KC_COLN );
            }
            return false;

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
                tap_code(KC_LEFT);
            } else if (record->event.pressed) {
                tap_code16(KC_LPRN);
            }
            return false;

        case LP_LBRC:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '[]' cursor in middle
                tap_code(KC_LBRC);
                tap_code(KC_RBRC);
                tap_code(KC_LEFT);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_LCBR:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '{}' cursor in middle
                tap_code16(KC_LCBR);
                tap_code16(KC_RCBR);
                tap_code(KC_LEFT);
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

        case LP_COMM:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '' one-shot shift or '```'
                mod_state = get_mods();
                uint8_t osm_state = get_oneshot_mods();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    SEND_STRING( "```" );
                    set_mods(mod_state);
                } else {
                    tap_code16( KC_COMM );
                }
                return false;
            } else if (record->event.pressed) {
                mod_state = get_mods();
                uint8_t osm_state = get_oneshot_mods();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16( KC_GRV );
                    set_mods(mod_state);
                    return false;
                }
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_DOT:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '. ' one-shot shift or '~/workspace/'
                mod_state = get_mods();
                uint8_t osm_state = get_oneshot_mods();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    SEND_STRING( "~/workspace/" );
                    set_mods(mod_state);
                } else {
                    tap_code( KC_DOT );
                    tap_code( KC_SPACE );
                    set_oneshot_mods(MOD_BIT(KC_LSFT));
                }
                return false;
            } else if (record->event.pressed) {
                mod_state = get_mods();
                uint8_t osm_state = get_oneshot_mods();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16( KC_TILD );
                    set_mods(mod_state);
                    return false;
                }
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_SPC:
            if (!record->tap.count && record->event.pressed) {
                // Intercept hold function to enable Tmux mode
                tmux_lock = true;
                return false;
            } else if (!record->tap.count && !record->event.pressed) {
                // hold release
                tmux_lock = false;
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
    printf("row: %d    col: %d\n", tap_hold_record->event.key.row, tap_hold_record->event.key.col);
    // Also allow same-hand holds when the other key is in the rows below the
    // alphas or first column.
    if (tap_hold_record->event.key.row == 3) { return true; }
    if (tap_hold_record->event.key.col == 0) { return true; }
    if (tap_hold_record->event.key.row == 1 && (tap_hold_record->event.key.col == 1 || tap_hold_record->event.key.col == 10)) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
        case K_SYMBS:
        case BSPC_NUM:
        case LP_SPC:
            return 0;  // Bypass Achordion for these keys.
    }
    return 800;  // Otherwise use a timeout of 800 ms.
}
#endif

void process_tmux_mode(uint16_t keycode, keyrecord_t *record) {
    if (tmux_lock) {
        // Ignore the following keys
        switch (keycode) {
            case K_SYMBS:
            case BSPC_NUM:
            case K_EXT:
            case KC_LSFT:
            case CAPS_NAV:
            case GUI_CTL:
                return;
        }
        // While TMUX is locked on, send C(A) before all other keys
        if (record->event.pressed) {
            tap_code16( C(KC_A) );
        }
    }
}

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

void show_layout_help(void) {
    #ifdef CORNE_FEATURES
    #elifdef ORTHO_FEATURES
    add_mods(MOD_BIT(KC_LCTL));
    #endif
    switch (get_highest_layer(layer_state)) {
        case 0:
            uint8_t osm_ralt = get_oneshot_mods() & MOD_BIT(KC_RALT);
            if ( osm_ralt ) {
                printf("help: altgr\n");
                clear_oneshot_mods();
                tap_code16( A(KC_INT1) );
            } else {
                printf("help: main\n");
                tap_code( KC_INT1 );
            }
            break;
        case EXTEND:
            printf("help: extend\n");
            tap_code( KC_INT2 );
            break;
        case NAV:
            printf("help: nav\n");
            tap_code( KC_INT3 );
            break;
        case SYSTEM:
            printf("help: system\n");
            tap_code( KC_INT4 );
            break;
#ifdef ORTHO_FEATURES
        case SYMBOLS:
            printf("help: symbols\n");
            tap_code( KC_INT5 );
            break;
#endif
        case NUMPAD:
            printf("help: numpad\n");
            tap_code( KC_INT6 );
            break;
#ifdef ORTHO_FEATURES
        case MEDIA:
            printf("help: media\n");
            tap_code( KC_LNG1 );
            break;
#endif
    }
    #ifdef ORTHO_FEATURES
    unregister_mods(MOD_BIT(KC_LCTL));
    #endif
}

void close_layout_help(void) {
    printf("close help\n");
    tap_code( KC_LNG9 );
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