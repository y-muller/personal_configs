
#pragma once

#include QMK_KEYBOARD_H

#include "layers_corne.h"
#include "custom_keys.h"
#include "tap_dance.h"

#include "combos.h"

#ifdef AZERTY_LAYER_ENABLE
#include "keymap_french.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak Home Row Mods
 * ,-----------------------------------------.                  ,-----------------------------------------.
 * |Esc/Md|   Q  |   W  |   F  |   P  |   B  |------.    ,------|   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|      |    |      |------+------+------+------+------+------|
 * |Tb/Ext|Sup/A |Alt/R |Sft/S |Ctrl/T|   G  |------|    |------|   M  |Ctrl/N|Sft/E |Alt/I |Sup/O |Enter |
 * |------+------+------+------+------+------|      |    |      |------+------+------+------+------+------|
 * |Esc/Ct|   Z  |   X  |   C  |   D  |   V  |------'    `------|   K  |   H  |   ,  |   .  |   /  |  '   |
 * `------+------+------+------+------+------+----.        ,----+------+------+------+------+------+------'
 *                           |??/Ext|Shift |⇪/Nav |        |Symbs |Space |Repeat|
 *                           `--------------------'        `--------------------'
 */
[COLEMAKH] = LAYOUT_split_3x6_3_ex2(
    ESC_MD,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     C_SYST,        CC_EMTG,  KC_J,     KC_L,     KC_U,     KC_Y,    KC_SCLN,  KC_BSPC,
    TAB_EXT,  HRM_A,    HRM_R,    HRM_S,    HRM_T,    KC_G,     KC_3,          KC_4,     KC_M,     HRM_N,    HRM_E,    HRM_I,   HRM_O,    ENT_MD,
    GUI_CTL,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                              KC_K,     KC_H,     LP_COMM,  LP_DOT,  LP_SLSH,  ALT_QUOT,
                                    K_NAV,    KC_LSFT,  CAPS_EXT,                    K_SYMBS,  LP_SPC,   K_FUNC
),


/* Colemak
 * ,-----------------------------------------.              ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |              |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |Extend|   A  |   R  |   S  |   T  |   G  |              |   M  |   N  |   E  |   I  |   O  |Enter |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |Esc/Ct|   Z  |   X  |   C  |   D  |   V  |              |   K  |   H  |   ,  |   .  |   /  |  '   |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |??/Ext|Shift |⇪/Nav |    |Symbs |Space |Repeat|
 *                           `--------------------'    `--------------------'
 */
[COLEMAK] = LAYOUT_split_3x6_3_ex2(
    ESC_MD,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     _______,       _______,  KC_J,     KC_L,     KC_U,     KC_Y,    KC_SCLN,  KC_BSPC,
    TAB_EXT,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     _______,       _______,  KC_M,     KC_N,     KC_E,     KC_I,    KC_O,     KC_ENT,
    GUI_CTL,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                              KC_K,     KC_H,     LP_COMM,  LP_DOT,  LP_SLSH,  ALT_QUOT,
                                    K_NAV,    KC_LSFT,  CAPS_EXT,                    K_SYMBS,  LP_SPC,   K_FUNC
),

/* Media
 * ,-----------------------------------------.                  ,-----------------------------------------.
 * |      |      |      |      |      |      |------.    ,------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |    |      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |------|    |------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|      |    |      |------+------+------+------+------+------|
 * |      |      |      |      |      |      |------'    `------|      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[MEDIA] = LAYOUT_split_3x6_3_ex2(
    KC_ESC,   KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_F20,   KC_F5,    _______,       _______,  C_LLOCK,  KC_BTN1,  KC_MS_U,  KC_BTN2,  XXXXXXX,  KC_PGUP,
    _______,  _______,  KC_BRID,  KC_BRIU,  CC_DISP,  XXXXXXX,  _______,       _______,  C(KC_PLUS),KC_MS_L, KC_MS_D,  KC_MS_R,  KC_UP,    KC_PGDN,
    _______,  KC_MPLY,  KC_MSTP,  KC_MPRV,  KC_MNXT,  XXXXXXX,                           C(KC_MINS),KC_BTN3, XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RIGHT,
                                    _______,  _______,  KC_ACL0,                      KC_HOME,  KC_SPC,   KC_END
),

/* Extend
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |PrvWin|      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[EXTEND] = LAYOUT_split_3x6_3_ex2(
    _______,  KC_ESC,   C(KC_W),  C(KC_F),  XXXXXXX,  KC_INS,    _______,       KC_MPLY,  KC_HOME,   KC_PGUP,  KC_UP,    KC_PGDN,  XXXXXXX,  KC_DEL,
    A(KC_TAB),C_OSWIN,  OSM_LALT, OSM_LSFT, OSM_LCTL, C_SELECT,  _______,       _______,  KC_END,    KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  S(KC_ENT),
    C_LLOCK,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_Y),                            S(KC_TAB), KC_TAB,   KS_AHOM,  KS_DPW,   KC_DEL,   K_GNOME,
                                    _______,  _______,  _______,                       _______,  _______,  _______
),

/* Nav
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[NAV] = LAYOUT_split_3x6_3_ex2(
    _______,  CG(KC_O), CG(KC_W), CG(KC_F), CG(KC_L), CG(KC_J), _______,       _______,  DM_PLY1,  A(KC_1),  A(KC_2),  A(KC_3),  A(KC_4),  XXXXXXX,
    C_ALTTAB, CG(KC_A), CG(KC_Y), CG(KC_S), CG(KC_B), CG(KC_T), _______,       _______,  XXXXXXX,  G(KC_F1), G(KC_F2), G(KC_F3), G(KC_F4), C(KC_PGUP),
    _______,  XXXXXXX,  CG(KC_X), CS(KC_C), CS(KC_V), XXXXXXX,                           XXXXXXX,  CC_SRCP,  CC_SRCN,  K_TAB_L,  K_TAB_R,  C(KC_PGDN),
                                    _______,  _______,  _______,                      A(KC_LEFT), K_SPC,  A(KC_RIGHT)
),

/* Symbols
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[SYMBOLS] = LAYOUT_split_3x6_3_ex2(
//    KC_GRV,   LP_PIPE,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,       _______,  KC_CIRC,  LP_AMPR,  C_PLSPLS, LP_EQL,   LP_EQEQ,  KC_BSPC,
//    KC_TILD,  LP_LCBR,  LP_LPRN,  LP_RPRN,  KC_RCBR,  KC_QUOT,  _______,       _______,  KC_BSLS,  KC_MINS,  KC_PLUS,  LP_SLSL,  KC_ASTR,  KC_ENT,
//    _______,  KC_LT,    LP_LBRC,  KC_RBRC,  KC_GT,    KC_DQUO,                           LP_EXLM,  KC_UNDS,  KC_SCLN,  LP_COLN,  KC_QUES,  KC_RWIN,
    KC_X,     LPS_GT,   KC_7,     KC_8,     KC_9,     KC_AT,    _______,       _______,  KC_DLR,   LP_LPRN,  LP_RPRN,  K_CBR,    KC_RCBR,  KC_BSPC,
    TAB_LMOD, HRM_DOT,  HRM_1,    HRM_2,    HRM_3,    KC_HASH,  _______,       _______,  LPS_EQL,  HRM_MINS, HRM_PLUS, HRM_SLSH, HRM_ASTR, ENT_RMOD,
    C_LLOCK,  LPS_LT,   KC_4,     KC_5,     KC_6,     LP_EXLM,                           LPS_AMP,  KC_UNDS,  LP_LBRC,  KC_RBRC,  LPS_PIPE, KC_RWIN,
                                    _______,  SFT_T(KC_0),  _______,                      _______,  _______,  _______
),

/* Numpad
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
//[NUMPAD] = LAYOUT_split_3x6_3(
//    KC_X,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
//    _______,  HRM_ASTR, LP_SLSL,  KC_PLUS,  KC_MINS,  KC_LT,                   KC_BSLS,  KC_4,     KC_5,     KC_6,     KC_0,     KC_ENT,
//    C_LLOCK,  LP_LPRN,  LP_LBRC,  KC_RBRC,  KC_RPRN,  KC_GT,                   KC_PERC,  KC_1,     KC_2,     KC_3,     KC_DOT,   LP_EQL,
//                                    _______,  _______,  _______,        _______,  _______,  _______
//),

//[NUMPAD] = LAYOUT_split_3x6_3_ex2(
//    KC_X,     KC_SLSH,  KC_7,     KC_8,     KC_9,     KC_PLUS,  _______,       _______,  KC_BSLS,  KC_LT,    KC_GT,    KC_HASH,  KC_DLR,   KC_BSPC,
//    _______,  KC_0,     KC_4,     KC_5,     KC_6,     KC_MINS,  _______,       _______,  KC_EQL,   OSM_LCTL, OSM_LSFT, OSM_LALT, C_OSWIN,  KC_ENT,
//    C_LLOCK,  LP_DOT,   KC_1,     KC_2,     KC_3,     KC_ASTR,                           KC_PERC,  LP_LPRN,  LP_LBRC,  KC_RBRC,  KC_RPRN,  LP_EQL,
//                                    _______,  KC_ENT,   _______,                      _______,  _______,  _______
//),

/* System
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[SYSTEM] = LAYOUT_split_3x6_3_ex2(
    C_CLMK1,  C_CLMK2,  KC_F7,    KC_F8,    KC_F9,    KC_F12,   _______,       KC_LSFT,  DM_REC1,  CC_RGBTG, RGB_MOD,  RGB_RMOD, CC_RGBRT, K_EECLR,
    C_AZERT,  C_1HAND,  KC_F1,    KC_F2,    KC_F3,    KC_F11,   _______,       _______,  DM_RSTP,  HRM_VAI,  HRM_HUI,  HRM_SAI,  HRM_SPI,  K_BOOT,
    XXXXXXX,  XXXXXXX,  KC_F4,    KC_F5,    KC_F6,    KC_F10,                            KC_SLEP,  RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  DB_TOGG,
                                    _______,  _______,  _______,                      _______,  _______,  _______
),

/* Left side Mods
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      | Supr | Alt  | Sft  | Ctrl |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[LMODS] = LAYOUT_split_3x6_3_ex2(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  C_OSWIN,  OSM_LALT, OSM_LSFT, OSM_LCTL, _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,                      _______,  _______,  _______
),


/* Right side Mods
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      | Ctrl | Sft  | Alt  | Supr |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[RMODS] = LAYOUT_split_3x6_3_ex2(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  OSM_LCTL, OSM_LSFT, OSM_LALT, C_OSWIN,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,                      _______,  _______,  _______
),

/* Left/Right side Mods
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      | Supr | Alt  | Sft  | Ctrl |      |              |      | Ctrl | Sft  | Alt  | Supr |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
[LRMODS] = LAYOUT_split_3x6_3_ex2(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  C_OSWIN,  OSM_LALT, OSM_LSFT, OSM_LCTL, _______,  _______,       _______,  _______,  OSM_LCTL, OSM_LSFT, OSM_LALT, C_OSWIN,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,                      _______,  _______,  _______
),

/* Colemak One Hand
 * ,-----------------------------------------.              ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |              |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |Extend|   A  |   R  |   S  |   T  |   G  |              |   M  |   N  |   E  |   I  |   O  |Enter |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |Esc/Ct|   Z  |   X  |   C  |   D  |   V  |              |   K  |   H  |   ,  |   .  |   /  |  '   |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |⇪/Ext |Shift |??/Nav|    |Symbs |Space |BS/Num|
 *                           `--------------------'    `--------------------'
 */
#ifdef SWAP_HANDS_ENABLE
[ONEHAND] = LAYOUT_split_3x6_3(
    ESC_MD,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                    KC_J,     KC_L,     KC_U,     KC_Y,    KC_SCLN,  KC_BSPC,
    TAB_EXT,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,                    KC_M,     KC_N,     KC_E,     KC_I,    KC_O,     KC_ENT,
    GUI_CTL,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                    KC_K,     KC_H,     LP_COMM,  LP_DOT,  LP_SLSH,  KC_QUOT,
                                    K_NAV,    SH_T(KC_SPC), TG(OH_SYMB),     TG(OH_SYMB), SH_T(KC_SPC), CAPS_EXT
),

[OH_SYMB] = LAYOUT_split_3x6_3_ex2(
    KC_X,     LPS_GT,   KC_7,     KC_8,     KC_9,     KC_AT,    _______,       _______,  KC_DLR,   LP_LPRN,  LP_RPRN,  LP_LCBR,  KC_RCBR,  KC_BSPC,
    TAB_LMOD, KC_DOT,   KC_1,     KC_2,     KC_3,     KC_HASH,  _______,       _______,  LPS_EQL,  KC_MINS,  KC_PLUS,  LP_SLSL,  LP_ASTCN, ENT_RMOD,
    OSM_LSFT, LPS_LT,   KC_4,     KC_5,     KC_6,     LP_EXLM,                           LPS_AMP,  KC_UNDS,  LP_LBRC,  KC_RBRC,  LPS_PIPE, OSM_LSFT,
                                    _______,  SH_T(KC_0),  _______,                   _______,  SH_T(KC_0),  _______
),

//[OH_EDIT] = LAYOUT_split_3x6_3_ex2(
//    _______,  KC_ESC,   C(KC_W),  C(KC_F),  XXXXXXX,  KC_INS,    _______,       _______,  KC_HOME,   KC_PGUP,  KC_UP,    KC_PGDN,  KS_DPW,   KC_DEL,
//    A(KC_TAB),C_OSWIN,  OSM_LALT, OSM_LSFT, OSM_LCTL, C_SELECT,  _______,       _______,  KC_END,    KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  S(KC_ENT),
//    C_LLOCK,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_Y),                            S(KC_TAB), KC_TAB,   KS_AHOM,  XXXXXXX,  KC_DEL,   XXXXXXX,
//                                    _______,  _______,  _______,                       _______,  _______,  _______
//),
#endif

/* AZERTY compatibility layers
 * Layout identical to Colemak HRM but send FR keys.
 * There is no expectation that the custom AltGr layer would be available,
 * so there is instead a layer with accents and extra symbols (in the same place if possible).
 */
#ifdef AZERTY_LAYER_ENABLE
[AZERTY] = LAYOUT_split_3x6_3_ex2(
    ESC_MD,   FR_Q,     FR_W,     FR_F,     FR_P,     FR_B,     C_SYST,        CC_EMTG,  FR_J,     FR_L,     FR_U,     FR_Y,     FR_SCLN,  KC_BSPC,
    TAB_EXT,  FR_HRM_A, FR_HRM_R, FR_HRM_S, FR_HRM_T, FR_G,     FR_3,          FR_4,     FR_M,     FR_HRM_N, FR_HRM_E, FR_HRM_I, FR_HRM_O, ENT_MD,
    GUI_CTL,  FR_Z,     FR_X,     FR_C,     FR_D,     FR_V,                              FR_K,     FR_H,     LP_COMM,  LP_DOT,   FR_SLSH,  FR_ALTQU,
                                    K_NAV,    KC_LSFT,  CAPS_EXT,                    FR_SYMBS,  LP_SPC,   K_FUNC
),

[FR_SYMB] = LAYOUT_split_3x6_3_ex2(
    FR_X,     LPS_GT,   FR_7,     FR_8,     FR_9,     FR_AT,    _______,       _______,  FR_DLR,   LP_LPRN,  LP_RPRN,  K_CBR,    FR_RCBR,  KC_BSPC,
    TAB_LMOD, HRM_DOT,  FR_HRM_1, FR_HRM_2, FR_HRM_3, FR_HASH,  _______,       _______,  LPS_EQL,  FR_HRM_MINS,HRM_PLUS,HRM_SLSH,HRM_ASTR, ENT_RMOD,
    C_LLOCK,  LPS_LT,   FR_4,     FR_5,     FR_6,     LP_EXLM,                           LPS_AMP,  FR_UNDS,  LP_LBRC,  FR_RBRC,  LPS_PIPE, KC_RWIN,
                                    _______,  FR_SFT_0,  _______,                 _______,  _______,  _______
),

[FR_ALTGR] = LAYOUT_split_3x6_3_ex2(
    _______,  FR_GRV,   _______,  FR_CIRC,  FR_DIAE,  _______,  _______,       _______,     _______,  _______,  _______,  FR_UGRV,  _______,  _______,
    _______,  FR_AGRV,  _______,  FR_MICR,  _______,  FR_EURO,  _______,       _______,     _______,  FR_EGRV,  FR_EACU,  _______,  _______,  _______,
    _______,  _______,  _______,  FR_CCED,  FR_DEG,   FR_PND,                               FR_CURR,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,                         _______,  _______,  _______
),
#endif

/* Blank
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |      |      |      |      |      |      |              |      |      |      |      |      |      |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |      |      |      |    |      |      |      |
 *                           `--------------------'    `--------------------'
 */
 /*
[BLANK] = LAYOUT_split_3x6_3_ex2(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,     _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,     _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                              _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,                         _______,  _______,  _______
),
*/

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [COLEMAKH]   = { ENCODER_CCW_CW(CC_ECCW, CC_ECW)},  // volume
    [COLEMAK]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
#ifdef SWAP_HANDS_ENABLE
    [ONEHAND]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
#endif
#ifdef AZERTY_LAYER_ENABLE
    [AZERTY]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FR_SYMB]   = { ENCODER_CCW_CW(S(KC_TAB), KC_TAB)},
    [FR_ALTGR]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
#endif
    [MEDIA]  = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},     // scrollwheel
//    [NUMPAD]   = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},   // 
    [EXTEND]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},   // 
    [NAV]      = { ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
    [SYSTEM]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [SYMBOLS]   = { ENCODER_CCW_CW(S(KC_TAB), KC_TAB)},
    [LMODS]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [RMODS]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LRMODS]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
#ifdef SWAP_HANDS_ENABLE
    [OH_SYMB]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
#endif
};
#endif

#ifdef SWAP_HANDS_ENABLE
    __attribute__ ((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
        {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
        {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
        {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
        {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
        {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}
    };
#    ifdef ENCODER_MAP_ENABLE
        const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {};
#    endif
#endif
