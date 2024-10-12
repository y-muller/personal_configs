
#include QMK_KEYBOARD_H

#include "y-muller.h"

#include "keymap_french.h"

#ifdef CORNE_FEATURES
#include "layers_corne.h"
#else
#ifdef ORTHO_FEATURES
#include "layers_ortho47.h"
#else
#include "layers_alice69.h"
#endif
#endif

#if defined(ACHORDION_ENABLE)
#include "features/achordion.h"
#endif

#ifdef LAYERLOCK_ENABLE
#include "features/layer_lock.h"
#endif

#include "custom_keys.h"
#include "tap_dance.h"
//#include "overrides.h"

#ifdef AZERTY_LAYER_ENABLE
#define TAP_CHECK_AZERTY( k1, k2 ) {\
    if (get_highest_layer(default_layer_state) == AZERTY) { \
        tap_code16(k2); \
    } else { \
        tap_code16(k1); \
    } \
}
#define DELMODS_CHECK_AZERTY( m1, m2 ) {\
    if (get_highest_layer(default_layer_state) == AZERTY) { \
        if (m2!=0) { del_mods(m2); clear_oneshot_mods(); } \
    } else { \
        if (m1!=0) { del_mods(m1); clear_oneshot_mods(); } \
    } \
}
#   else
#define TAP_CHECK_AZERTY( k1, k2 ) {\
    tap_code16(k1); \
}
#define DELMODS_CHECK_AZERTY( m1, m2 ) {\
    del_mods(m1); clear_oneshot_mods(); \
}
#   endif

#ifdef RGB_MATRIX_ENABLE
HSV prev_hsv;
int prev_rgb_mode;
extern uint8_t indicator_brightness;
#endif

user_runtime_config_t user_state;
userspace_config_t userspace_config;
static bool        device_suspended = false;

bool alt_encoder_mode = false;
bool macro_recording_mode = false;

// Select mode
bool select_mode = false;
bool select_mode_word = false;
bool select_mode_line = false;

static bool alt_tab_active = false;

extern bool tmux_lock;

#include "private.h"
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    //printf("remember %d\n", keycode);
    switch (keycode) {
        case K_NAV:
        case K_FUNC:
            return false;
    }

    return true;  // Other keys can be repeated.
}

static void process_left_magic(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_A:
        case HRM_A:
            SEND_STRING(/*a*/"tion"); return;
        case KC_I: SEND_STRING(/*i*/"tion"); return;
        case KC_H: SEND_STRING(/*h*/"ere"); return;
        case KC_M: SEND_STRING(/*m*/"ent"); return;
        case KC_Y: SEND_STRING(/*y*/"ou"); return;
        case KC_X: tap_code16(KC_BSPC); SEND_STRING(PRIV_COMPANY_NAME); return;
        case KC_AT: SEND_STRING(/*@*/PRIV_DOMAIN_1); return;
        case KC_HASH: SEND_STRING(/*#*/"define "); return;
    }

    tap_code(keycode);
}

static void process_right_magic(uint16_t keycode, uint8_t mods) {
    switch (keycode) {
        case KC_A:
        case HRM_A:
            SEND_STRING(/*a*/"tion"); return;
        case KC_S: SEND_STRING(/*s*/"sion"); return;
        case KC_T: SEND_STRING(/*t*/"heir"); return;
        case KC_W: SEND_STRING(/*w*/"hich"); return;
        case KC_X: tap_code16(KC_BSPC); SEND_STRING(PRIV_COMPANY_EMAIL); return;
        case KC_AT: SEND_STRING(/*@*/PRIV_COMPANY_DOMAIN); return;
        case KC_HASH: SEND_STRING(/*#*/"include "); return;
    }

    tap_code(keycode);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined(ACHORDION_ENABLE)
    if (!process_achordion(keycode, record)) { return false; }
#endif

#ifdef LAYERLOCK_ENABLE
    if (!process_layer_lock(keycode, record, C_LLOCK)) { return false; }
#endif

    process_tmux_mode(keycode, record);
    
    if (!process_select_mode(keycode, record)) { return false; }

    uint8_t mod_state = get_mods();
    uint8_t osm_state = get_oneshot_mods();

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

        case C_MEDIA_MO:
            if (record->event.pressed) {
                layer_on(MEDIA);
            } else {
                layer_off(MEDIA);
            }
            return false;
#endif

        case K_NAV:
            // Intercept tap as Left Magic
            if (record->tap.count && record->event.pressed) {
                process_left_magic(get_last_keycode(), get_last_mods());
                return false;
            }
            return true;

        case K_FUNC:
            // Intercept tap as Right Magic
            if (record->tap.count && record->event.pressed) {
                process_right_magic(get_last_keycode(), get_last_mods());
                return false;
            }
            return true;

        case C_CLMK1:
            set_single_persistent_default_layer(COLEMAK);
#           ifdef SWAP_HANDS_ENABLE
                autoshift_disable();
#           endif
            return false;

        case C_CLMK2:
            set_single_persistent_default_layer(COLEMAKH);
#           ifdef SWAP_HANDS_ENABLE
                autoshift_disable();
#           endif
            return false;

#ifdef AZERTY_LAYER_ENABLE
        case C_AZERT:
            set_single_persistent_default_layer(AZERTY);
#           ifdef SWAP_HANDS_ENABLE
                autoshift_disable();
#           endif
            return false;
#endif

        case C_1HAND:
#           ifdef SWAP_HANDS_ENABLE
                set_single_persistent_default_layer(ONEHAND);
                autoshift_enable();
#           endif
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

//        case C_NUMLK:
//            if (record->event.pressed) {
//                if (is_oneshot_layer_active()) {
//                    reset_oneshot_layer();
//                    layer_on(NUMPAD);
//                } else {
//                    layer_off(NUMPAD);
//                }
//            }
//            return false;

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
                    rgb_matrix_mode/*_noeepro*/(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv/*_noeeprom*/(HSV_OFF);
                }
            }
            return false;

        case CC_RGBRT:
            // set RGB to defaults
            if (record->event.pressed) {
                //rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                rgb_matrix_sethsv_noeeprom(255,255,255);
            }
            return false;

#endif
        case RGB_VAI:
            if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    indicator_brightness += 25;
                }
                return false;
            }
            return true;

        case RGB_VAD:
            if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    indicator_brightness -= 25;
                }
                return false;
            }
            return true;

        case CC_DISP: // handle the display switch key on Thinhpad (F7)
            if (record->event.pressed) {
                host_system_send( SYSTEM_DISPLAY_TOGGLE_INT_EXT );
            } else {
                host_system_send( 0 );
            }
            return false; // Skip all further processing of this key

        case C_ALTTAB:
            if (!alt_tab_active) {
                alt_tab_active = true;
                register_code(KC_LALT);
            }
            if (record->event.pressed) {
                tap_code16(KC_TAB);
            }
            return false;

        case C_TMUX: // 
            if (record->event.pressed) {
                tmux_lock = true;
            } else {
                tmux_lock = false;
            }
            return false; // Skip all further processing of this key

        case C_SYST:
            if (record->event.pressed) {
                printf("system on\n");
                layer_on(SYSTEM);
            } else {
                printf("system off\n");
                layer_off(SYSTEM);
            }
            return false;

        case C_HELP:
            if (record->event.pressed) {
                show_layout_help();
            } else {
                close_layout_help();
            }
            return false;

        case ALT_QUOT:
            // HRM suppresses Alt if no other key is pressed
            // A long press here activates app menus, etc...
            if (!record->tap.count && record->event.pressed) {
                // Intercept hold function for  Alt
                register_mods(MOD_BIT(KC_LALT));
                return false;
            } else if (!record->tap.count && !record->event.pressed) {
                unregister_mods(MOD_BIT(KC_LALT));
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case HRM_DOT:
            if (record->tap.count && record->event.pressed) {
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    DELMODS_CHECK_AZERTY(0, MOD_MASK_SHIFT);
                    TAP_CHECK_AZERTY(KC_COMM, FR_COMM);
                    set_mods(mod_state);
                } else {
                    // Send single '.'
                    TAP_CHECK_AZERTY(KC_DOT, FR_DOT);
                }
            }
            return false;

        case HRM_PLUS:
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16( KC_PLUS );
                } else {
                    unregister_code16( KC_PLUS );
                }
                return false;
            }
            return true;             // Return true for normal processing of hold

        case HRM_SLSH:
            if (record->tap.count && record->event.pressed) {
                // Intercept shifted tap for a comma
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_BSLS, FR_BSLS);
                    set_mods(mod_state);
                    return false;
                } else {
                    TAP_CHECK_AZERTY(KC_SLSH, FR_SLSH); 
                    return false;
                }
            }
            return true;             // Return true for normal processing of tap keycode

        case HRM_ASTR:
            if (record->tap.count && record->event.pressed) {
                // Intercept shifted tap for a colon
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    DELMODS_CHECK_AZERTY(0, MOD_MASK_SHIFT);
                    TAP_CHECK_AZERTY(KC_COLN, FR_COLN);
                    set_mods(mod_state);
                } else {
                    // Send single '*'
                    TAP_CHECK_AZERTY(KC_ASTR, FR_ASTR);
                }
            }
            return false;

        case K_SYMBS:
            //printf("Symb taps:%d pressed:%d\n", record->tap.count, record->event.pressed);
            if (record->tap.count == 1) {
                if (!record->event.pressed) {
                    if (osm_state & MOD_BIT(KC_RALT)) {
                        clear_oneshot_mods();
                    } else {
                        set_oneshot_mods(MOD_BIT(KC_RALT));
                    }
                }
                return false;
            } else if (record->tap.count >= 2) {
                if (record->event.pressed) {
                    set_oneshot_mods(MOD_BIT(KC_RALT));
                    layer_on(SYMBOLS);
                } else {
                    layer_off(SYMBOLS);
                }
                return false;                
            }
            return true;

#ifdef AZERTY_LAYER_ENABLE
        case FR_SYMBS:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function for FR_SYMB layer
                layer_on(FR_SYMB);
                return false;
            } else if (!record->tap.count && !record->event.pressed) {
                layer_off(FR_SYMB);
                return false;
            }
            return true;             // Return true for one-shot FR_ALT layer

        case FR_SFT_0:
            if (record->tap.count) {
                if (record->event.pressed) {
                    register_code16( FR_0 );
                } else {
                    unregister_code16( FR_0 );
                }
                return false;
            }
            return true;             // Return true for normal processing of hold

#endif

        case C_OSWIN:
            if (record->event.pressed) {
                add_oneshot_mods(MOD_BIT(KC_LWIN));
                return false;
            }
            return true;

        case C_VIMCMD:
            // ESC colon
            if (record->event.pressed) {
                caps_word_off();
                tap_code16( KC_ESC );
                // handle Colemak/Azerty difference
#ifdef AZERTY_LAYER_ENABLE
                if (get_highest_layer(default_layer_state) == AZERTY) {
                    tap_code16( FR_COLN );
                } else
#endif
                {
                    tap_code16( KC_COLN );
                }
            }
            return false;

        case LPS_PIPE:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send '||', shift adds surrounding spaces
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code(KC_SPC);
                    TAP_CHECK_AZERTY(KC_PIPE, FR_PIPE);
                    TAP_CHECK_AZERTY(KC_PIPE, FR_PIPE);
                    tap_code(KC_SPC);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_PIPE, FR_PIPE);
                    TAP_CHECK_AZERTY(KC_PIPE, FR_PIPE);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
//                    del_mods(MOD_MASK_SHIFT);
//                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_QUES, FR_QUES);
//                    set_mods(mod_state);
                } else {
                    // Send single '&'
                    TAP_CHECK_AZERTY(KC_PIPE, FR_PIPE);
                }
            }
            return false;

        case LP_PIPE:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send ' || '
                tap_code(KC_SPC);
                tap_code16(KC_PIPE);
                tap_code16(KC_PIPE);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                caps_word_off();
                tap_code16(KC_PIPE);
            }
            return false;

        case LP_ASTCN:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send ':', shift sends '::'
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    tap_code16(KC_COLN);
                    tap_code16(KC_COLN);
                } else {
                    tap_code16(KC_COLN);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    tap_code16(KC_COLN);
                    tap_code16(KC_COLN);
                } else {
                    tap_code16(KC_ASTR);
                }
            }
            return false;

        case LPS_AMP:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send '&&', shift adds surrounding spaces
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code(KC_SPC);
                    TAP_CHECK_AZERTY(KC_AMPR, FR_AMPR);
                    TAP_CHECK_AZERTY(KC_AMPR, FR_AMPR);
                    tap_code(KC_SPC);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_AMPR, FR_AMPR);
                    TAP_CHECK_AZERTY(KC_AMPR, FR_AMPR);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    // Send ' & '*/*/
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code(KC_SPC);
                    TAP_CHECK_AZERTY(KC_AMPR, FR_AMPR);
                    tap_code(KC_SPC);
                    set_mods(mod_state);
                } else {
                    // Send single '&'
                    TAP_CHECK_AZERTY(KC_AMPR, FR_AMPR);
                }
            }
            return false;

        case LPS_LT:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send '<=', shift sends '"'
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_DQUO, FR_DQUO);
                    TAP_CHECK_AZERTY(KC_DQUO, FR_DQUO);
                    tap_code16(KC_LEFT);
                    set_mods(mod_state);
                } else {
                    DELMODS_CHECK_AZERTY(MOD_MASK_SHIFT, MOD_MASK_SHIFT);
                    TAP_CHECK_AZERTY(KC_LT, FR_LABK);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                if (osm_state & MOD_BIT(KC_RALT)) {
                    tap_code16(KC_GRV);
                } else if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    DELMODS_CHECK_AZERTY(0, MOD_MASK_SHIFT);
                    TAP_CHECK_AZERTY(KC_DQUO, FR_DQUO);
                } else {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_LT, FR_LABK);
                }
            }
            return false;

        case LPS_GT:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send '>=', shift sends '''
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_QUOT, FR_QUOT);
                    TAP_CHECK_AZERTY(KC_QUOT, FR_QUOT);
                    tap_code16(KC_LEFT);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_GT, FR_RABK);
                    TAP_CHECK_AZERTY(KC_EQL, KC_EQL);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                if (osm_state & MOD_BIT(KC_RALT)) {
                    tap_code16(KC_TILD);
                } else if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_QUOT, FR_QUOT);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_GT, FR_RABK);
                }
            }
            return false;

        case LP_AMPR:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' && '
                caps_word_off();
                tap_code(KC_SPC);
                tap_code16(KC_AMPR);
                tap_code16(KC_AMPR);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                caps_word_off();
                tap_code16(KC_AMPR);
            }
            return false;

        case LP_EXLM:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '!=', shift adds surrounding spaces
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    DELMODS_CHECK_AZERTY(MOD_MASK_SHIFT, MOD_MASK_SHIFT);
                    tap_code(KC_SPC);
                    TAP_CHECK_AZERTY(KC_EXLM, FR_EXLM);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                    tap_code(KC_SPC);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_EXLM, FR_EXLM);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                // Send single '!', shift '\'
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY(KC_BSLS, FR_BSLS);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_EXLM, FR_EXLM);
                }
            }
            return false;

        case LPS_EQL:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '==', shift adds surrounding spaces
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code(KC_SPC);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                    tap_code(KC_SPC);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                if (osm_state & MOD_BIT(KC_RALT)) {
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                } else if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    // Send single '=', shift adds surrounding spaces
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code(KC_SPC);
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                    tap_code(KC_SPC);
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY(KC_EQL, FR_EQL);
                }
            }
            return false;

        case LP_EQL:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' = '
                caps_word_off();
                tap_code(KC_SPC);
                tap_code(KC_EQL);
                tap_code(KC_SPC);
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_EQEQ:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ' == '
                caps_word_off();
                tap_code(KC_SPC);
                tap_code16(KC_EQL);
                tap_code16(KC_EQL);
                tap_code(KC_SPC);
            } else if (record->event.pressed) {
                caps_word_off();
                tap_code16(KC_EQL);
                tap_code16(KC_EQL);
            }
            return false;

        case LP_SLSH:
            if (!record->tap.count) {
                if (record->event.pressed) {
                    caps_word_off();
                     // Intercept hold function to send ~/ or ../
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
                }
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

        case LP_SLSL:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                 // Intercept hold function to send '==', shift adds surrounding spaces
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code(KC_BSLS);
                    tap_code(KC_BSLS);
                    set_mods(mod_state);
                } else {
                    tap_code16(KC_SLSH);
                    tap_code16(KC_SLSH);
                    tap_code(KC_SPC);
                }
            } else if (record->event.pressed) {
                caps_word_off();
                // Override AltGr to get the division character
                if (osm_state & MOD_BIT(KC_RALT)) {
                    tap_code16(KC_5);
                // Send single '=', shift adds surrounding spaces
                } else if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16(KC_BSLS);
                    set_mods(mod_state);
                } else {
                    tap_code(KC_SLSH);
                }
            }
            return false;

        case LP_COLN:
            if (!record->tap.count && record->event.pressed) {
                caps_word_off();
                tap_code16(KC_COLN); // Intercept hold function to send ::
                tap_code16(KC_COLN);
                return false;
            } else if (record->event.pressed) {
                caps_word_off();
                tap_code16(KC_COLN);
            }
            return false;

        case LP_LPRN:
            //printf("  tap.count=%d, thing=%d\n", record->tap.count, record->event.interrupted);
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '()' cursor in middle
                caps_word_off();
                TAP_CHECK_AZERTY(KC_LPRN, FR_LPRN);
                TAP_CHECK_AZERTY(KC_RPRN, FR_RPRN);
                tap_code(KC_LEFT);
            } else if (record->event.pressed) {
                if (osm_state & MOD_BIT(KC_RALT)) {
                    TAP_CHECK_AZERTY(KC_9, FR_9);
                } else {
                    caps_word_off();
                    TAP_CHECK_AZERTY(KC_LPRN, FR_LPRN);
                }
            }
            return false;

        case LP_LBRC:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '[]' cursor in middle
                caps_word_off();
                TAP_CHECK_AZERTY(KC_LBRC, FR_LBRC);
                TAP_CHECK_AZERTY(KC_RBRC, FR_RBRC);
                tap_code(KC_LEFT);
                return false;
            } else if (record->event.pressed) {
                caps_word_off();
                TAP_CHECK_AZERTY(KC_LBRC, FR_LBRC);
            }
            return false;

        case LP_LCBR:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '{}' cursor in middle
                caps_word_off();
                TAP_CHECK_AZERTY(KC_LCBR, FR_LCBR);
                TAP_CHECK_AZERTY(KC_RCBR, FR_RCBR);
                tap_code(KC_LEFT);
            } else if (record->event.pressed) {
                caps_word_off();
                TAP_CHECK_AZERTY(KC_LCBR, FR_LCBR);
            }
            return false;

        case LP_RPRN:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ');↵'
                caps_word_off();
                TAP_CHECK_AZERTY(KC_RPRN, FR_RPRN);
                TAP_CHECK_AZERTY(KC_SCLN, FR_SCLN);
                tap_code16(KC_ENT);
            } else if (record->event.pressed) {
                if (osm_state & MOD_BIT(KC_RALT)) {
                    // ???
                TAP_CHECK_AZERTY(KC_0, FR_0);
                } else {
                    caps_word_off();
                TAP_CHECK_AZERTY(KC_RPRN, FR_RPRN);
                }
            }
            return false;

        case LP_COMM:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '' one-shot shift or '```'
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    //SEND_STRING( "```" );
                    TAP_CHECK_AZERTY( KC_GRV, FR_GRV )
                    TAP_CHECK_AZERTY( KC_GRV, FR_GRV )
                    TAP_CHECK_AZERTY( KC_GRV, FR_GRV )
                    set_mods(mod_state);
                } else {
                    //tap_code16( KC_COMM );
                    TAP_CHECK_AZERTY( KC_COMM, FR_COMM )
                }
                return false;
            } else if (record->event.pressed) {
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    //tap_code16( KC_GRV );
                    TAP_CHECK_AZERTY( KC_GRV, FR_GRV )
                    set_mods(mod_state);
                    return false;
                } else {
                    TAP_CHECK_AZERTY( KC_COMM, FR_COMM )
                }
            }
            return false; 

        case LP_DOT:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '. ' one-shot shift or '~/workspace/'
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    SEND_STRING( "~/workspace/" );
                    set_mods(mod_state);
                } else {
                    TAP_CHECK_AZERTY( KC_DOT, FR_DOT )
                    tap_code( KC_SPACE );
                    set_oneshot_mods(MOD_BIT(KC_LSFT));
                }
                return false;
            } else if (record->event.pressed) {
                caps_word_off();
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    TAP_CHECK_AZERTY( KC_TILD, FR_TILD )
                    set_mods(mod_state);
                    return false;
                } else {
                    TAP_CHECK_AZERTY( KC_DOT, FR_DOT )
                }
            }
            return false;

        case LP_SPC:
            if (!record->tap.count && record->event.pressed) {
                // Intercept hold function to enable Tmux mode
                user_state.is_tmux = true;
                return false;
            } else if (!record->tap.count && !record->event.pressed) {
                // hold release
                user_state.is_tmux = false;
                return false;
            }
            return true;             // Return true for normal processing of tap keycode

#ifdef AZERTY_LAYER_ENABLE
        case FL_COMM:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '' one-shot shift or '```'
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16( FR_GRV ); tap_code16( FR_GRV ); tap_code16( FR_GRV );
                    set_mods(mod_state);
                } else {
                    tap_code16( FR_COMM );
                }
                caps_word_off();
                return false;
            } else if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16( FR_GRV );
                    set_mods(mod_state);
                    return false;
                }
            }
            return true;             // Return true for normal processing of tap keycode

        case FL_DOT:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '. ' one-shot shift
                    caps_word_off();
                    tap_code16( FR_DOT );
                    tap_code( KC_SPACE );
                    set_oneshot_mods(MOD_BIT(KC_LSFT));
                return false;
            } else if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    caps_word_off();
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16( FR_TILD );
                    set_mods(mod_state);
                    return false;
                } else {
                    caps_word_off();
                    tap_code16( FR_DOT );
                }
            }
            return false;

        case FR_ALTQU:
            print("alt quot\n");
            if (record->tap.count && record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    print("dquot\n");
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16( FR_DQUO );
                    set_mods(mod_state);
                    return false;
                }
            }
            return true;

        case FL_SLSL:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send '==', shift adds surrounding spaces
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16(FR_BSLS);
                    tap_code16(FR_BSLS);
                    set_mods(mod_state);
                } else {
                    tap_code16(FR_SLSH);
                    tap_code16(FR_SLSH);
                    tap_code(KC_SPC);
                }
                 caps_word_off();
           } else if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16(FR_BSLS);
                    set_mods(mod_state);
                } else {
                    tap_code16(FR_SLSH);
                }
                caps_word_off();
            }
            return false;

        case FL_ASTCN:
            if (!record->tap.count && record->event.pressed) {
                 // Intercept hold function to send ':', shift sends '::'
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16(FR_COLN);
                    tap_code16(FR_COLN);
                    set_mods(mod_state);
                } else {
                    tap_code16(FR_COLN);
                }
                caps_word_off();
            } else if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT || osm_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    clear_oneshot_mods();
                    tap_code16(FR_COLN);
                    tap_code16(FR_COLN);
                    set_mods(mod_state);
                } else {
                    tap_code16(FR_ASTR);
                }
                caps_word_off();
            }
            return false;

#endif

        // Language-aware custom keys
        case C_UNDO:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( C(KC_Z), C(FR_Z) )
            }
            return false;

        case C_UNDS:
            if (record->event.pressed) {
                DELMODS_CHECK_AZERTY(0, MOD_MASK_SHIFT);
                TAP_CHECK_AZERTY( KC_UNDS, FR_UNDS )
            }
            return false;

        case C_MINS:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_MINS, FR_MINS)
            }
            return false;

        case C_QUOT:
            if (record->event.pressed) {
                DELMODS_CHECK_AZERTY(MOD_MASK_SHIFT, MOD_MASK_SHIFT);
                TAP_CHECK_AZERTY( KC_QUOT, FR_QUOT )
            }
            return false;

        case C_DQUO:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_DQUO, FR_DQUO)
                caps_word_off();
            }
            return false;

        case C_COLN:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_COLN, FR_COLN )
                caps_word_off();
            }
            return false;

        case C_SCLN:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_SCLN, FR_SCLN )
                caps_word_off();
            }
            return false;

        case C_EXLM:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_EXLM, FR_EXLM )
                caps_word_off();
            }
            return false;

        case C_PERC:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_PERC, FR_PERC )
            }
            return false;

        case C_BSLS:
            if (record->event.pressed) {
                TAP_CHECK_AZERTY( KC_BSLS, FR_BSLS)
                caps_word_off();
            }
            return false;


        default:
            return true; // Process all other keycodes normally
    }
}

void matrix_scan_user(void) {
#if defined(ACHORDION_ENABLE)
    achordion_task();
#endif

    if (alt_tab_active) {
        if (IS_LAYER_OFF(NAV)) {
            unregister_code(KC_LALT);
            alt_tab_active = false;
        }
    }
}

/**
 * @brief Housekeeping task
 *
 * sets user_state config to be synced later or just used. Also runs other "every tick" tasks
 */
__attribute__((weak)) void housekeeping_task_keymap(void) {}
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
#   ifdef UNICODE_COMMON_ENABLE
        user_state.unicode_mode        = unicode_config.input_mode;
        user_state.unicode_typing_mode = unicode_typing_mode;
#   endif // UNICODE_COMMON_ENABLE
#   ifdef SWAP_HANDS_ENABLE
        user_state.swap_hands = swap_hands;
#   endif // SWAP_HANDS_ENABLE
        //user_state.host_driver_disabled = get_keyboard_lock();
#   ifdef CAPS_WORD_ENABLE
        user_state.is_caps_word = is_caps_word_on();
#   endif // CAPS_WORD_ENABLE
#   ifdef CAPS_WORD_ENABLE
        user_state.is_leader = leader_sequence_active();
#   endif // CAPS_WORD_ENABLE
#if defined(SPLIT_TRANSACTION_IDS_USER)
    housekeeping_task_transport_sync();
#endif // SPLIT_KEYBOARD && SPLIT_TRANSACTION_IDS_USER
    }
    housekeeping_task_keymap();
}

#if defined(ACHORDION_ENABLE)
bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
    printf("row: %d    col: %d\n", tap_hold_record->event.key.row, tap_hold_record->event.key.col);
    // Also allow same-hand holds when the other key is in the rows below the
    // alphas or first column.
    if (tap_hold_record->event.key.row == 3 || tap_hold_record->event.key.row == 7) { print("achordion allow\n"); return true; }
    if (tap_hold_record->event.key.col == 0) { return true; }
    if (tap_hold_record->event.key.row == 1 && (tap_hold_record->event.key.col == 1 || tap_hold_record->event.key.col == 10)) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
        case K_SYMBS:
#ifdef AZERTY_LAYER_ENABLE
        case FR_SYMBS:
#endif
//        case BSPC_NUM:
        case LP_SPC:
            print("achordion bypass\n");
            return 0;  // Bypass Achordion for these keys.
    }
    return 800;  // Otherwise use a timeout of 800 ms.
}
#endif

void process_tmux_mode(uint16_t keycode, keyrecord_t *record) {
    if (user_state.is_tmux) {
        // Ignore the following keys
        switch (keycode) {
            case K_SYMBS:
//            case BSPC_NUM:
            case K_EXT:
            case KC_LSFT:
            case CAPS_EXT:
            case GUI_CTL:
                return;
        }
        // While TMUX is locked on, send C(A) before all other keys
        if (record->event.pressed) {
            tap_code16( C(KC_A) );
        }
    }
}

bool process_select_mode(uint16_t keycode, keyrecord_t *record) {
    if (keycode == C_SELECT) {
        if (record->event.pressed) {
            select_mode = true;
        } else {
            select_mode = false;
            select_mode_word = false;
            select_mode_line = false;
        }
    }
    if (select_mode && record->event.pressed) {
        switch (keycode) {
            case KC_RIGHT:
                if (!select_mode_word) {
                    select_mode_word = true;
                    select_mode_line = false;
                    tap_code16( C(KC_RIGHT) );
                    tap_code16( C(KC_LEFT) );
                    tap_code16( CS(KC_RIGHT) );
                } else {
                    tap_code16( CS(KC_RIGHT) );
                }
                return false;
            case KC_LEFT:
                if (!select_mode_word) {
                    select_mode_word = true;
                    select_mode_line = false;
                    tap_code16( C(KC_LEFT) );
                    tap_code16( C(KC_RIGHT) );
                    tap_code16( CS(KC_LEFT) );
                } else {
                    tap_code16( CS(KC_LEFT) );
                }
                return false;
            case KC_DOWN:
                if (!select_mode_line) {
                    select_mode_line = true;
                    select_mode_word = false;
                    tap_code16( KC_HOME );
                    tap_code16( KC_HOME );
                    tap_code16( S(KC_DOWN) );
                } else {
                    tap_code16( S(KC_DOWN) );
                }
                return false;
            case KC_UP:
                if (!select_mode_line) {
                    select_mode_line = true;
                    select_mode_word = false;
                    tap_code16( KC_END );
                    tap_code16( KC_RIGHT );
                    tap_code16( S(KC_UP) );
                } else {
                    tap_code16( S(KC_UP) );
                }
                return false;
            case KC_PGDN:
                if (!select_mode_line) {
                    select_mode_line = true;
                    select_mode_word = false;
                    tap_code16( KC_HOME );
                    tap_code16( KC_HOME );
                    tap_code16( S(KC_PGDN) );
                } else {
                    tap_code16( S(KC_PGDN) );
                }
                return false;
            case KC_PGUP:
                if (!select_mode_line) {
                    select_mode_line = true;
                    select_mode_word = false;
                    tap_code16( KC_END );
                    tap_code16( KC_RIGHT );
                    tap_code16( S(KC_PGUP) );
                } else {
                    tap_code16( S(KC_PGUP) );
                }
                return false;
        }
    }
    return true;
}

#ifdef OLD_REPO
void dynamic_macro_record_start_user(int8_t direction) {
#else
bool dynamic_macro_record_start_user(int8_t direction) {
#endif
    macro_recording_mode = true;
#ifndef OLD_REPO
    return true;
#endif
}

#ifdef OLD_REPO
void dynamic_macro_record_end_user(int8_t direction) {
#else
bool dynamic_macro_record_end_user(int8_t direction) {
#endif
    macro_recording_mode = false;
#ifndef OLD_REPO
    return true;
#endif
}

bool caps_word_press_user(uint16_t keycode) {
    printf("caps_word_press_user code %d %d\n", keycode, KC_QUOT);
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
        case KC_QUOT: 
        case K_CAPS: // Tap dance for Caps Word itself
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

void show_layout_help(void) {
    #ifdef CORNE_FEATURES
    printf("corne\n");
    #else
    #ifdef ORTHO_FEATURES
    add_mods(MOD_BIT(KC_LCTL));
    #endif
    #endif
    uint8_t osm_ralt;
    switch (get_highest_layer(layer_state)) {
        case 0:
            osm_ralt = get_oneshot_mods() & MOD_BIT(KC_RALT);
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
//        case NUMPAD:
//            printf("help: numpad\n");
//            tap_code( KC_INT6 );
//            break;
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

#if defined(SPLIT_TRANSACTION_IDS_USER)
    keyboard_post_init_transport_sync();
#endif // SPLIT_KEYBOARD && SPLIT_TRANSACTION_IDS_USER

#ifdef SWAP_HANDS_ENABLE
    if (get_highest_layer(default_layer_state) != ONEHAND) {
        autoshift_disable();
    }
#endif

#ifdef BLUETOOTH_POST_INIT
    if (get_transport() == TRANSPORT_BLUETOOTH) {
        prev_hsv = rgb_matrix_get_hsv();
        prev_rgb_mode = rgb_matrix_get_mode();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_BLUE);
    }
#endif  // BLUETOOTH_POST_INIT
}

/**
 * @brief Checks to see if device is suspended
 *
 * @return true
 * @return false
 */
bool is_device_suspended(void) {
    return device_suspended;
}

/**
 * @brief Sets the local variable for device suspended
 *
 * @param status
 */
void set_is_device_suspended(bool status) {
#if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    send_device_suspend_state(status);
#endif
    device_suspended = status;
}


//tap_dance_action_t tap_dance_actions[] = {
//    [TD_BOOT] = ACTION_TAP_DANCE_FN(td_bootloader),
//    [TD_EECLR] = ACTION_TAP_DANCE_FN(td_clear_eeprom),
////    [TD_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(td_leader_each, td_leader_finished, NULL),
////    [TD_BSLS] = ACTION_TAP_DANCE_FN_ADVANCED(td_bsls_each, td_bsls_finished, td_bsls_reset),
//#ifdef LEADER_ENABLE
//    [TD_RSFT_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(/*td_rsft_lead_each*/ NULL, td_rsft_lead_finished, td_rsft_lead_reset),
//#endif
//    [TD_ALTGR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_altgr_finished, td_altgr_reset),
//    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset),
//    [TD_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_tmux_finished, td_tmux_reset)
//};
