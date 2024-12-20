
#pragma once

#include QMK_KEYBOARD_H

#include "layers_corne.h"
#include "custom_keys.h"
#include "tap_dance.h"

#include "combos.h"

#ifdef AZERTY_LAYER_ENABLE
#include "keymap_french.h"
#endif

#include "keymap_wrappers.h"

#define LAYOUT_wrapper(...) LAYOUT_split_3x6_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak Home Row Mods
 * ,-----------------------------------------.              ,-----------------------------------------.
 * |Esc/Md|   Q  |   W  |   F  |   P  |   B  |              |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |Tb/Ext|Ext/A |Alt/R |Sft/S |Ctrl/T|   G  |              |   M  |Ctrl/N|Sft/E |Alt/I |Ext/O |Enter |
 * |------+------+------+------+------+------|              |------+------+------+------+------+------|
 * |Esc/Ct|   Z  |   X  |   C  |   D  |   V  |              |   K  |   H  |   ,  |   .  |   /  |  '   |
 * `------+------+------+------+------+------+----.    ,----+------+------+------+------+------+------'
 *                           |⇪/Ext |Shift |??/Nav|    |Symbs |Space |BS/Num|
 *                           `--------------------'    `--------------------'
 */
[COLEMAKH] = LAYOUT_wrapper(
    ESC_MD,   _________________COLEMAK_L1________________,                     _________________COLEMAK_R1________________,  KC_BSPC,
    TAB_EXT,  _______________COLEMAK_HRM_L2______________,                     _______________COLEMAK_HRM_R2______________,  ENT_MD,
    GUI_CTL,  _________________COLEMAK_L3________________,                     _________________COLEMAK_R3________________,  ALT_QUOT,
                                    K_NAV,    KC_LSFT,  CAPS_EXT,       K_SYMBS,  LP_SPC,   K_FUNC
),


/* Colemak
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
[COLEMAK] = LAYOUT_wrapper(
    ESC_MD,   _________________COLEMAK_L1________________,                     _________________COLEMAK_R1________________,  KC_BSPC,
    TAB_EXT,  _________________COLEMAK_L2________________,                     _________________COLEMAK_R2________________,  ENT_MD,
    GUI_CTL,  _________________COLEMAK_L3________________,                     _________________COLEMAK_R3________________,  ALT_QUOT,
                                    K_NAV,    KC_LSFT,  CAPS_EXT,       K_SYMBS,  LP_SPC,   K_FUNC
),

/* Media
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
[MEDIA] = LAYOUT_wrapper(
    _______________MEDIA_L1____6COLNS__________________,                       _______________MEDIA_R1____6COLNS__________________,
    _______________MEDIA_L2____6COLNS__________________,                       _______________MEDIA_R2____6COLNS__________________,
    _______________MEDIA_L3____6COLNS__________________,                       _______________MEDIA_R3____6COLNS__________________,
                                  _______,  _______,  KC_ACL0,          KC_HOME,  KC_SPC,   KC_END
),

/* Extend
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
[EXTEND] = LAYOUT_wrapper(
    ______________EXTEND_L1____6COLNS__________________,                       ______________EXTEND_R1____6COLNS__________________,
    ______________EXTEND_L2____6COLNS__________________,                       ______________EXTEND_R2____6COLNS__________________,
    ______________EXTEND_L3____6COLNS__________________,                       ______________EXTEND_R3____6COLNS__________________,
                                _______,  _______,  _______,            _______,  KC_SPC,   _______
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
[NAV] = LAYOUT_wrapper(
    ________________NAV_L1____6COLNS___________________,                       ________________NAV_R1____6COLNS___________________,
    ________________NAV_L2____6COLNS___________________,                       ________________NAV_R2____6COLNS___________________,
    ________________NAV_L3____6COLNS___________________,                       ________________NAV_R3____6COLNS___________________,
                                _______,  _______,  _______,             A(KC_LEFT), K_SPC,  A(KC_RIGHT)
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
[SYMBOLS] = LAYOUT_wrapper(
    KC_X,     _________________SYMBOLS_L1________________,                     _________________SYMBOLS_R1________________,  KC_BSPC,
    TAB_LMOD, _________________SYMBOLS_L2________________,                     _________________SYMBOLS_R2________________,  ENT_RMOD,
    C_LLOCK,  _________________SYMBOLS_L3________________,                     _________________SYMBOLS_R3________________,  KC_RWIN,
                                    _______,  SFT_0,   _______,         _______,  _______,  _______
),

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
[SYSTEM] = LAYOUT_wrapper(
    ______________SYSTEM_L1____6COLNS__________________,                       ______________SYSTEM_R1____6COLNS__________________,
    ______________SYSTEM_L2____6COLNS__________________,                       DM_RSTP,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  K_BOOT,
    ______________SYSTEM_L3____6COLNS__________________,                       ______________SYSTEM_R3____6COLNS__________________,
                                    _______,  _______,  _______,        _______,  _______,  _______
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
[LMODS] = LAYOUT_split_3x6_3(
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  C_OSWIN,  OSM_LALT, OSM_LSFT, OSM_LCTL, _______,                 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,        _______,  _______,  _______
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
[RMODS] = LAYOUT_split_3x6_3(
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  OSM_LCTL, OSM_LSFT, OSM_LALT, C_OSWIN,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,        _______,  _______,  _______
),

#ifdef SWAP_HANDS_ENABLE
/* Colemak Swap Hand
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
[SWAP_HANDS] = LAYOUT_split_3x6_3(
    ESC_MD,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                    KC_J,     KC_L,     KC_U,     KC_Y,    KC_SCLN,  KC_BSPC,
    TAB_EXT,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,                    KC_M,     KC_N,     KC_E,     KC_I,    KC_O,     KC_ENT,
    GUI_CTL,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                    KC_K,     KC_H,     LP_COMM,  LP_DOT,  LP_SLSH,  KC_QUOT,
                                    CAPS_NAV, SH_T(KC_SPC), K_EXT,          K_SYMBS, SH_T(KC_SPC), BSPC_NUM
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
[BLANK] = LAYOUT_split_3x6_3(
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                 _______,  _______,  _______,  _______,  _______,  _______,
                                    _______,  _______,  _______,        _______,  _______,  _______
),
*/

};

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{ 0, 4}, { 1, 4}, { 2, 4}, { 3, 4}, { 4, 4}, { 5, 4}},
  {{ 0, 5}, { 1, 5}, { 2, 5}, { 3, 5}, { 4, 5}, { 5, 5}},
  {{ 0, 6}, { 1, 6}, { 2, 6}, { 3, 6}, { 4, 6}, { 5, 6}},
                             {{ 0, 7}, { 1, 7}, { 2, 7}},

  {{ 0, 0}, { 1, 0}, { 2, 0}, { 3, 0}, { 4, 0}, { 5, 0}},
  {{ 0, 1}, { 1, 1}, { 2, 1}, { 3, 1}, { 4, 1}, { 5, 1}},
  {{ 0, 2}, { 1, 2}, { 2, 2}, { 3, 2}, { 4, 2}, { 5, 2}},
                             {{ 0, 3}, { 1, 3}, { 2, 3}},
};

