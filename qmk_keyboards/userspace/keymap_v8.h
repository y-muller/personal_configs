
#ifndef _KEYMAP_V8_H_
#define _KEYMAP_V8_H_

#include QMK_KEYBOARD_H

#include "layers_v8.h"
//#include "custom_keys.h"
//#include "bluetooth_keys.h"
#include "tap_dance.h"
//#include "unicode.h"
//
//#include "combos.h"

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif

#ifndef MACRO_ANSI_69
#define LAYOUT_69_auto LAYOUT_69_ansi
#else
#define LAYOUT_69_auto LAYOUT_ansi_69
#endif

// Home Row Mods
#define HRM_A LGUI_T(KC_A)
#define HRM_R LALT_T(KC_R)
#define HRM_S LSFT_T(KC_S)
#define HRM_T LCTL_T(KC_T)
#define HRM_N LCTL_T(KC_N)
#define HRM_E LSFT_T(KC_E)
#define HRM_I LALT_T(KC_I)
#define HRM_O LGUI_T(KC_O)

// long press keys
#define LP_COLN LT(0,KC_COLN) // tap: ':', long: '::'
#define LP_SLSH LT(0,KC_SLSH) // tap: '/', long: '~/'
#define LP_SLSL LT(1,KC_SLSH) // tap: '/', long: '// '  - symbols layer
#define LP_PIPE LT(0,KC_PIPE) // tap: '|', long: ' || '
#define LP_EQL  LT(0,KC_EQL)  // tap: '=', long: ' = '
#define LP_EQEQ LT(0,KC_PEQL) // tap: '==', long: ' == '
#define LP_AMPR LT(0,KC_AMPR) // tap: '&', long: ' && '
#define LP_EXLM LT(0,KC_EXLM) // tap: '!', long: ' !! '
#define LP_LPRN LT(0,KC_LPRN) // tap: '(', long: '()'
#define LP_LBRC LT(0,KC_LBRC) // tap: '[', long: '[]'
#define LP_LCBR LT(1,KC_LCBR) // tap: '{', long: '{}' - same keys as LBRC so change the layer
#define LP_RPRN LT(0,KC_RPRN) // tap: ')', long: ');↵'
#define LP_DOT  LT(0,KC_DOT)  // tap: '.', long: '. ' one-shot shift

// AltGr / Compose
#define K_SYMB TD(TD_ALTGR)

// Boot on double tap
#define K_BOOT TD(TD_BOOT)

// Clear EEPROM on triple tap
#define K_EECLR TD(TD_EECLR)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[COLEMAK] = LAYOUT_69_auto(     // the host is set to QWERTY
    KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          _______,
    KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_B,    KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_PGUP,
    _______, HRM_A,    HRM_R,    HRM_S,   HRM_T,   KC_G,              KC_M,    HRM_N,   HRM_E,   HRM_I,    HRM_O,    KC_QUOT,  KC_ENT,           KC_PGDN,
    KC_LSFT,          KC_X,     KC_C,    KC_D,    KC_V,    KC_Z,     _______,  KC_K,    KC_H,    KC_COMM,  LP_DOT,   LP_SLSH,  _______, KC_UP,
    KC_LCTL,KC_LWIN,  KC_LALT,           KC_LSFT,          _______,    MO(SYSTEM),         KC_SPC,           K_SYMB,            KC_LEFT, KC_DOWN, KC_RGHT),

[SYMBOLS] = LAYOUT_69_auto(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
  KC_GRV,   LP_PIPE,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  LP_AMPR,  KC_ASTR,  KC_QUES,  _______, _______,  _______,  _______,           _______,
  KC_TILD,  LP_LCBR,  LP_LPRN,  LP_RPRN,  KC_RCBR,  KC_QUOT,            KC_BSLS,  KC_MINS,  KC_PLUS,  LP_SLSL,  KC_SCLN,  _______,  _______,           _______,
  _______,            KC_LT,    LP_LBRC,  KC_RBRC,  KC_GT,    KC_DQUO,  _______,  LP_EXLM,  KC_UNDS,  LP_EQL,   LP_EQEQ,  KC_COLN,  _______, _______,
  _______,  _______,  _______,            _______,            _______,  _______,            _______,            _______,            _______, _______,  _______),


[SYSTEM] = LAYOUT_69_auto(
    _______, KC_MUTE,  KC_VOLD,  KC_VOLU, KC_F20,  KC_BRID, KC_BRIU,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
    _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,         K_BOOT,
    RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,           _______, _______, KC_SLEP, _______,  _______,  _______,  _______,          DB_TOGG,
    _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
    _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, K_EECLR),

/*
[MODEL] = LAYOUT_69_auto(
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,
  _______,  _______,  _______,            _______,            _______,  _______,            _______,            _______,            _______, _______,  _______),
*/
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) { return false; }
#endif

    switch (keycode) {
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
                uint8_t mod_state = get_mods();
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
    printf("row: %d    col: %d\n", tap_hold_record->event.key.row, tap_hold_record->event.key.col);
    // Also allow same-hand holds when the other key is in the rows below the
    // alphas or first column.
    if (tap_hold_record->event.key.row == 4) { return true; }
    if (tap_hold_record->event.key.col == 0) { return true; }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}
#endif


#endif