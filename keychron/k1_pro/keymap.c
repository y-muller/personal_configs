/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "keymap_french.h"
#include "keymap_colemak.h"
#include "rgb_map.h"

#include "print.h"

enum layers {
  AZERTY,       // host is set to Azerty
  AZ_ALT,       // symbol layer for Azerty
  COLEMAK,      // host is set to En US
  CLMK_CM,      // host is set to En Colemak
  QWERTY,       // reverts to En US Qwerty layout, host is set to the same, physical layout of keys doesn't match
  EXTEND,       // main utility layer
  NAV,          // navigation shortcuts, start apps
  FUNC,         // 
  SYSTEM,       // control RGB, keyboard function, switch default layer
  NUMPAD,       // numpad
};


enum my_keycodes {
  CC_DISP = SAFE_RANGE, // Thinkpad display switching F7
  CC_MINRGB,            // RGB mostly off, used for indicators
  CC_ELOCK,             // Lock Extend layer
  CC_TEST
};

// KC_CAPS becomes Esc/Ctrl
#define ESC_CTL LCTL_T(KC_ESC)
// or EXTEND
//#define L_EXTEND LT(0, KC_NO)
#define L_EXTEND OSL(EXTEND)
#define L_NAV OSL(NAV)

// KC_RALT becomes Compose/RAlt with Compose set to RWin in Gnome
#define CMP_RALT RALT_T(KC_RWIN)

// Shortcut for Crtl+Gui, Ctrl+Shift
#define LCG(kc) (QK_LCTL | QK_LGUI | (kc))
#define LCS(kc) (QK_LCTL | QK_LSFT | (kc))

// shortcut for One Shot Mods
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_LALT OSM(MOD_LALT)

// Delete Previous Word (Ctrl+Backspace)
#define KS_DPW LCTL(KC_BSPC)
// Alt+Home (real Home for CodeLite: start of line)
#define KS_AHOM A(KC_HOME)

// dummy key to process override SHIFT + EXTEND
#define KS_SYSLYR C(KC_F13)

uint8_t one_shot_active_mods = 0;
bool trilayer_system_state = false;

// This is called when the override activates and deactivates. Enable the fn layer on activation and disable on deactivation
bool shift_mod_layer(bool key_down, void *layer) {
    if (key_down) {
        print("shift_mod_layer ON\n");
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        print("shift_mod_layer OFF\n");
        layer_off((uint8_t)(uintptr_t)layer);
    }   
    return false;
}

//const key_override_t shift_mod_layer_override = {.trigger_mods = MOD_BIT(KC_LSFT),                       //
//                                   .layers                 = ~(1 << SYSTEM),                                          //
//                                   .suppressed_mods        = MOD_BIT(KC_LSFT),                       //
//                                   .options                = ko_option_no_unregister_on_other_key_down,                 //
//                                   .negative_mod_mask      = (uint8_t) ~(MOD_BIT(KC_LSFT)),          //
//                                   .custom_action          = shift_mod_layer,                                           //
//                                   .context                = (void *)SYSTEM,                                          //
//                                   .trigger                = KS_SYSLYR,                                                     //
//                                   .replacement            = KC_NO,                                                     //
//                                   .enabled                = NULL};
                                   
// Key overrides
const key_override_t left_scrollwheel_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_L, KC_WH_L, (1 << EXTEND));
const key_override_t right_scrollwheel_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_R, KC_WH_R, (1 << EXTEND));
const key_override_t up_scrollwheel_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_U, KC_WH_U, (1 << EXTEND));
const key_override_t down_scrollwheel_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_D, KC_WH_D, (1 << EXTEND));
// AZERTY number row and other symbols overrides
const key_override_t fr1_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_1, FR_EXLM, (1 << AZERTY));
const key_override_t fr2_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_2, FR_AT, (1 << AZERTY));
const key_override_t fr3_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_3, FR_HASH, (1 << AZERTY));
const key_override_t fr4_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_4, FR_DLR, (1 << AZERTY));
const key_override_t fr5_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_5, FR_PERC, (1 << AZERTY));
const key_override_t fr6_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_6, FR_PND    , (1 << AZERTY));
const key_override_t fr7_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_7, FR_AMPR, (1 << AZERTY));
const key_override_t fr8_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_8, FR_ASTR, (1 << AZERTY));
const key_override_t fr9_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_9, FR_LPRN, (1 << AZERTY));
const key_override_t fr0_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_0, FR_RPRN, (1 << AZERTY));
const key_override_t fr_mins_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_MINS, FR_UNDS, (1 << AZERTY));
const key_override_t fr_quot_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_QUOT, FR_DQUO, (1 << AZERTY));
const key_override_t fr_scln_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_SCLN, FR_COLN, (1 << AZERTY));
const key_override_t fr_comm_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_COMM, FR_LABK, (1 << AZERTY));
const key_override_t fr_dot_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_DOT, FR_RABK, (1 << AZERTY));
const key_override_t fr_slsh_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_SLSH, FR_QUES, (1 << AZERTY));
const key_override_t fr_lbrc_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_LBRC, FR_LCBR, (1 << AZERTY));
const key_override_t fr_rbrc_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_RBRC, FR_RCBR, (1 << AZERTY));
const key_override_t fr_bsls_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_BSLS, FR_PIPE, (1 << AZERTY));
// layer with double keys
//const key_override_t system_layer_override = ko_make_basic(MOD_MASK_SHIFT, L_EXTEND, KS_SYSLYR);


const key_override_t **key_overrides = (const key_override_t *[]){
    &left_scrollwheel_override,
    &right_scrollwheel_override,
    &up_scrollwheel_override,
    &down_scrollwheel_override,
    &fr1_override,
    &fr2_override,
    &fr3_override,
    &fr4_override,
    &fr5_override,
    &fr6_override,
    &fr7_override,
    &fr8_override,
    &fr9_override,
    &fr0_override,
    &fr_mins_override,
    &fr_quot_override,
    &fr_scln_override,
    &fr_comm_override,
    &fr_dot_override,
    &fr_slsh_override,
    &fr_lbrc_override,
    &fr_rbrc_override,
    &fr_bsls_override,
//    &shift_mod_layer_override,
    NULL // Null terminate the array of overrides!
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [AZERTY] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,      KC_F11,   KC_F12,   KC_PSCR,  KC_CTANA, RGB_MOD,
        KC_GRV,   FR_1,     FR_2,     FR_3,     FR_4,     FR_5,     FR_6,     FR_EQL,   FR_7,     FR_8,     FR_9,     FR_0,        FR_MINS,  KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   FR_Q,     FR_W,     FR_F,     FR_P,     FR_B,     FR_LBRC,  FR_J,     FR_L,     FR_U,     FR_Y,     FR_SCLN,     FR_QUOT,  FR_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        ESC_CTL,  FR_A,     FR_R,     FR_S,     FR_T,     FR_G,     FR_RBRC,  FR_M,     FR_T,     FR_E,     FR_I,     FR_O,        KC_ENT,
        OSM_LSFT,           FR_X,     FR_C,     FR_D,     FR_V,     FR_Z,     FR_SLSH,  FR_K,     FR_H,     FR_COMM,  FR_DOT,                KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 TL_LOWR,  MO(AZ_ALT),  TL_UPPR,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),


    [AZ_ALT] = LAYOUT_tkl_ansi(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,
        FR_GRV,   _______,  _______,  _______,  _______,  FR_EURO,  FR_CIRC,  _______,  _______,  _______,  _______,  _______,     _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  FR_MICR,  _______,  FR_DIAE,     FR_TILD,  _______,  _______,  _______,  _______,
        _______,  FR_AGRV,  _______,  _______,  _______,  FR_EGRV,  _______,  _______,  _______,  FR_EACU,  _______,  _______,     _______,
        _______,            _______,  FR_CCED,  FR_DEG,   _______,  _______,  _______,  _______,  _______,  _______,  _______,               _______,            _______,
        _______,  _______,  _______,                            _______,                                    _______,  _______,     _______,  _______,  _______,  _______,  _______),


    [QWERTY] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   QK_LEAD,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        ESC_CTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        OSM_LSFT,           KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,            KC_UP,
        OSM_LCTL, KC_LWIN,  KC_LALT,                                KC_SPC,                                 TL_LOWR,  CMP_RALT, TL_UPPR,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),


//    [COLEMAK] = LAYOUT_tkl_ansi(  // Standard Colemak
//        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   QK_LEAD,  RGB_MOD,
//        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
//        KC_BSPC,  KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_TAB,   KC_DEL,   KC_END,   KC_PGDN,
//        ESC_CTL,  KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,
//        OSM_LSFT,           KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,            KC_UP,
//        OSM_LCTL, KC_LWIN,  KC_LALT,                                KC_SPC,                                 TL_LOWR,  CMP_RALT, TL_UPPR,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),


    [COLEMAK] = LAYOUT_tkl_ansi(  // Colemak CAW with the host set to US
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   MO(SYSTEM),   KS_SYSLYR,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_EQL,   KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_LBRC,  KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        L_EXTEND, KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_RBRC,  KC_M,     KC_N,     KC_E,     KC_I,     KC_O,               KC_ENT,
        OSM_LSFT,           KC_X,     KC_C,     KC_D,     KC_V,     KC_Z,     KC_SLSH,  KC_K,     KC_H,     KC_COMM,  KC_DOT,             OSM_RSFT,           KC_UP,
        OSM_LCTL, KC_LWIN,  KC_LALT,                                KC_SPC,                                 L_EXTEND, CMP_RALT, L_NAV,    OSM_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT),


    [CLMK_CM] = LAYOUT_tkl_ansi(  // Colemak CAW wtth the host set to Colemak
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   QK_LEAD,  RGB_MOD,
        CM_GRV,   CM_1,     CM_2,     CM_3,     CM_4,     CM_5,     CM_6,     CM_EQL,   CM_7,     CM_8,     CM_9,     CM_0,     CM_MINS,  KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   CM_Q,     CM_W,     CM_F,     CM_P,     CM_B,     CM_LBRC,  CM_J,     CM_L,     CM_U,     CM_Y,     CM_SCLN,  CM_QUOT,  CM_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        L_EXTEND, CM_A,     CM_R,     CM_S,     CM_T,     CM_G,     CM_RBRC,  CM_M,     CM_N,     CM_E,     CM_I,     CM_O,               KC_ENT,
        OSM_LSFT,           CM_X,     CM_C,     CM_D,     CM_V,     CM_Z,     CM_SLSH,  CM_K,     CM_H,     CM_COMM,  CM_DOT,             OSM_RSFT,           KC_UP,
        OSM_LCTL, KC_LWIN,  KC_LALT,                                KC_SPC,                                 TL_LOWR,  CMP_RALT, TL_UPPR,  OSM_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT),


    [EXTEND] = LAYOUT_tkl_ansi(
        KC_NO,              G(KC_F1), G(KC_F2), G(KC_F3), G(KC_F4), _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_WH_L,  KC_WH_R,  _______,
        A(KC_GRV),A(KC_1),  A(KC_2),  A(KC_3),  A(KC_4),  A(KC_5),  A(KC_6), _______,   A(KC_7),  A(KC_8),  A(KC_9),  A(KC_0),_______,  _______,  KC_BTN3,  _______,  KC_WH_U,
        A(KC_TAB),KC_ESC,   C(KC_W),  C(KC_F),  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_DEL,   KC_MENU,  CC_ELOCK, KC_BTN1,  KC_BTN2,  KC_WH_D,
        _______,  OSM_LALT, KC_ACL0,  OSM_LSFT, OSM_LCTL, KC_LWIN,  _______,  KC_END,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,            _______,
        CW_TOGG,            C(KC_X),  C(KC_C),  _______,  C(KC_V),  C(KC_Z),  _______,  _______,  KS_AHOM,  KS_DPW,   _______,            _______,            KC_MS_U,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R),


    [NAV] = LAYOUT_tkl_ansi(
        _______,            G(KC_F1),  G(KC_F2),  G(KC_F3),  G(KC_F4),  _______,   _______,   _______,   _______,   _______,    _______,  _______,  _______,  _______,  TO(SYSTEM),  _______,
        _______, LCA(KC_1), LCA(KC_2), LCA(KC_3), LCA(KC_4), LCA(KC_5), LCA(KC_6), LCA(KC_7), LCA(KC_8), LCA(KC_9), LCA(KC_0),  _______,  _______,  _______,  _______,  _______,  _______,
        _______, _______,   LCG(KC_W), LCG(KC_F), LCA(KC_P), LCG(KC_B),  LCG(KC_Y), _______,   _______,   LCG(KC_O), LCG(KC_Y),  LCA(KC_LBRC),  LCA(KC_RBRC),  KC_BSLS,  _______,  _______,  _______,
        _______, _______,   _______,   LCG(KC_S),   _______,  _______,    _______,   _______,   G(KC_F1),  G(KC_F2),  G(KC_F3),   G(KC_F4),            _______,
        KC_CAPS,            _______,   LCS(KC_C),  _______, LCS(KC_V),  LCG(KC_Z), _______,   _______,   _______,   _______,    _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                             _______,   _______,    _______,  _______,  _______,  _______,  _______),


    [FUNC] = LAYOUT_tkl_ansi(
        _______,            KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_F20,   KC_BRID,  KC_BRIU,  CC_DISP,  _______,  KC_MPLY,  _______,  KC_MSEL,  KC_MYCM,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        CW_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,            _______,  _______,  _______,  _______, TG(NUMPAD),_______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),


    [SYSTEM] = LAYOUT_tkl_ansi(
        TO(SYSTEM),         KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______, DF(COLEMAK),DF(CLMK_CM),DF(AZERTY),DF(QWERTY),     _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  DB_TOGG,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),


    [NUMPAD] = LAYOUT_tkl_ansi(
        TG(NUMPAD),       KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_F20,   KC_BRID,  KC_BRIU,  CC_DISP,  _______,  KC_MPLY,  _______,  KC_MSEL,  KC_MYCM,  _______,  _______,  RGB_TOG,
        _______,  KC_P1,    KC_P2,    KC_P3,    KC_P4,    KC_P5,    KC_P6,    KC_NO,    KC_P7,    KC_P8,    KC_P9,    KC_PAST,  KC_PMNS,  _______,  _______,  _______,  KC_WH_U,
        _______,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_P4,    KC_P5,    KC_P6,    KC_PSLS,  _______,  _______,  _______,  _______,  KC_WH_D,
        _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_P1,    KC_P2,    KC_P3,    KC_PPLS,            KC_PENT,
        _______,            KC_NO,    _______,  _______,  _______,  KC_NO,    KC_NO,    KC_COMM,  KC_P0,    KC_P0,    KC_PDOT,            KC_BTN1,            KC_MS_U,
        _______,  _______,  _______,                                KC_PENT,                                _______,  _______,  KC_BTN3,  KC_BTN2,  KC_MS_L,  KC_MS_D,  KC_MS_R)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CC_ELOCK:
            if (record->event.pressed) {
                if (is_oneshot_layer_active())
                {
                    reset_oneshot_layer();
                    layer_on(EXTEND);
                } else {
                    layer_off(EXTEND);
                }
            }
            return false;

        case CC_MINRGB:
            // TODO: create an RGB mode in black with no effect (fake off)
            return true;

//        case KS_SYSLYR:
//            if (record->event.pressed) {
//                set_oneshot_layer(EXTEND, ONESHOT_START);
//                //clear_oneshot_layer_state(ONESHOT_PRESSED);
//            } else {
//                //clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
//                clear_oneshot_layer_state(ONESHOT_PRESSED);
//            }
//            return false;

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

//void oneshot_layer_changed_user(uint8_t layer) {
//}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    // Turn off RGB on undefined layer keys
    if (get_highest_layer(layer_state) > 3) {
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
        rgb_matrix_set_color(LED_QUOT, RGB_RED); // Delete
        rgb_matrix_set_color(LED_O, RGB_RED);    // Backspace
    }

    // Caps lock - turn all the modifier red
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(50, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(63, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(74, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(76, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(77, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(78, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(80, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(81, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(82, 255, 0, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(83, 255, 0, 0);
    }
    else if (is_caps_word_on()) {
        RGB_MATRIX_INDICATOR_SET_COLOR(50, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(63, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(74, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(76, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(77, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(78, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(80, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(81, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(82, 0, 255, 0);
        RGB_MATRIX_INDICATOR_SET_COLOR(83, 0, 255, 0);
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
            RGB_MATRIX_INDICATOR_SET_COLOR(63, 0, 255, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(74, 0, 255, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(76, 0, 255, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(77, 0, 255, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(82, 0, 255, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(83, 0, 255, 255);
        }
        else if (one_shot_active_mods & MOD_MASK_CTRL)
        {
            //RGB_MATRIX_INDICATOR_SET_COLOR(63, 255, 0, 255);
            //RGB_MATRIX_INDICATOR_SET_COLOR(74, 255, 0, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(76, 255, 0, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(77, 255, 0, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(82, 255, 0, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(83, 255, 0, 255);
        }
    }
    return false;
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    } else if (leader_sequence_three_keys(KC_T, KC_M, KC_W)) {
        // Leader, t, m, w => tmux work
        SEND_STRING( SS_LCTL(SS_LGUI("b")) SS_DELAY(250) SS_LSFT(SS_LCTL("t")) "tmuxinator start work");
    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
        // Leader, a, s => GUI+S
        tap_code16(LGUI(KC_S));
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    bool extend_layer_is_off = ((state & (1<<EXTEND)) == 0);
    bool nav_layer_is_off = ((state & (1<<NAV)) == 0);
    uprintf("layer_state_set_user: state:%d previous=%d extend=%d nav=%d\n", state, trilayer_system_state, extend_layer_is_off, nav_layer_is_off);
    if (trilayer_system_state && (extend_layer_is_off || nav_layer_is_off)) {
        uprintf("layer_state_set_user: system not on anymore\n");
        // System layer was on but not anymore, turn off the other 2 layers
        state = state & ~(1<<EXTEND);
        state = state & ~(1<<NAV);
        state = state & ~(1<<SYSTEM);
    } else {
        state = update_tri_layer_state(state, EXTEND, NAV, SYSTEM);
    }
    trilayer_system_state = ((state & (1<<SYSTEM)) != 0);
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    one_shot_active_mods = mods;
    uprintf("Oneshot mods %d\n", mods);
}
