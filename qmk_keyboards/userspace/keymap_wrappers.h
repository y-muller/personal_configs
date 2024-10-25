// Copyright 2024 y-muller
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2020 @jola5
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
*/
// clang-format off

#define _________________COLEMAK_L1________________       KC_Q,     KC_W,     KC_F,     KC_P,    KC_B
#define _________________COLEMAK_L2________________       KC_A,     KC_R,     KC_S,     KC_T,    KC_G
#define _________________COLEMAK_L3________________       KC_Z,     KC_X,     KC_C,     KC_D,    KC_V

#define _________________COLEMAK_R1________________       KC_J,     KC_L,     KC_U,     KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_M,     KC_N,     KC_E,     KC_I,    KC_O
#define _________________COLEMAK_R3________________       KC_K,     KC_H,     LP_COMM,  LP_DOT,  LP_SLSH

#define _______________COLEMAK_HRM_L2______________       HRM_A,    HRM_R,    HRM_S,    HRM_T,   KC_G
#define _______________COLEMAK_HRM_R2______________       KC_M,     HRM_N,    HRM_E,    HRM_I,   HRM_O




#define _________________SYMBOLS_L1________________       LPS_GT,   KC_7,     KC_8,     KC_9,    KC_AT
#define _________________SYMBOLS_L2________________       HRM_DOT,  HRM_1,    HRM_2,    HRM_3,   KC_HASH
#define _________________SYMBOLS_L3________________       LPS_LT,   KC_4,     KC_5,     KC_6,    LP_EXLM

#define _________________SYMBOLS_R1________________       KC_DLR,   LP_LPRN,  LP_RPRN,  K_CBR,   KC_RCBR
#define _________________SYMBOLS_R2________________       LPS_EQL,  HRM_MINS, HRM_PLUS, HRM_SLSH,HRM_ASTR
#define _________________SYMBOLS_R3________________       LPS_AMP,  KC_UNDS,  LP_LBRC,  KC_RBRC, LPS_PIPE



#define _______________MEDIA_L1____6COLNS__________________       KC_ESC,   KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_F20,   KC_F5
#define _______________MEDIA_L2____6COLNS__________________       _______,  _______,  KC_BRID,  KC_BRIU,  CC_DISP,  XXXXXXX
#define _______________MEDIA_L3____6COLNS__________________       _______,  KC_MPLY,  KC_MSTP,  KC_MPRV,  KC_MNXT,  XXXXXXX

#define _______________MEDIA_R1____6COLNS__________________       C_LLOCK,  KC_BTN1,  KC_MS_U,  KC_BTN2,  XXXXXXX,  KC_PGUP
#define _______________MEDIA_R2____6COLNS__________________       C(KC_PLUS),KC_MS_L, KC_MS_D,  KC_MS_R,  KC_UP,    KC_PGDN
#define _______________MEDIA_R3____6COLNS__________________       C(KC_MINS),KC_BTN3, XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_RIGHT



#define ______________EXTEND_L1____6COLNS__________________       _______,  KC_ESC,   C(KC_W),  C(KC_F),  XXXXXXX,  KC_INS
#define ______________EXTEND_L2____6COLNS__________________       A(KC_TAB),C_OSWIN,  OSM_LALT, OSM_LSFT, OSM_LCTL, C_SELECT
#define ______________EXTEND_L3____6COLNS__________________       C_LLOCK,  C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_Y)

#define ______________EXTEND_R1____6COLNS__________________       KC_HOME,   KC_PGUP,  KC_UP,    KC_PGDN,  XXXXXXX,  KC_DEL
#define ______________EXTEND_R2____6COLNS__________________       KC_END,    KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,  S(KC_ENT)
#define ______________EXTEND_R3____6COLNS__________________       S(KC_TAB), KC_TAB,   KS_AHOM,  KS_DPW,   KC_DEL,   K_GNOME



#define ________________NAV_L1____6COLNS___________________       _______,  CG(KC_O), CG(KC_W), CG(KC_F), CG(KC_L), CG(KC_J)
#define ________________NAV_L2____6COLNS___________________       C_ALTTAB, CG(KC_A), CG(KC_Y), CG(KC_S), CG(KC_B), CG(KC_T)
#define ________________NAV_L3____6COLNS___________________       _______,  XXXXXXX,  CG(KC_X), CS(KC_C), CS(KC_V), XXXXXXX

#define ________________NAV_R1____6COLNS___________________       DM_PLY1,  A(KC_1),  A(KC_2),  A(KC_3),  A(KC_4),  XXXXXXX
#define ________________NAV_R2____6COLNS___________________       XXXXXXX,  G(KC_F1), G(KC_F2), G(KC_F3), G(KC_F4), C(KC_PGUP)
#define ________________NAV_R3____6COLNS___________________       XXXXXXX,  K_TAB_L,  K_TAB_R,  CC_SRCP,  CC_SRCN,  C(KC_PGDN)



#define ______________SYSTEM_L1____6COLNS__________________       C_CLMK,   XXXXXXX,  KC_F7,    KC_F8,    KC_F9,    KC_F12
#define ______________SYSTEM_L2____6COLNS__________________       C_AZERT,  XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F11
#define ______________SYSTEM_L3____6COLNS__________________       C_1HAND,  XXXXXXX,  KC_F4,    KC_F5,    KC_F6,    KC_F10

#define ______________SYSTEM_R1____6COLNS__________________       DM_REC1,  CC_RGBTG, RGB_MOD,  RGB_RMOD, CC_RGBRT, K_EECLR
#define ______________SYSTEM_R2____6COLNS__________________       DM_RSTP,  HRM_VAI,  HRM_HUI,  HRM_SAI,  HRM_SPI,  K_BOOT
#define ______________SYSTEM_R3____6COLNS__________________       KC_SLEP,  RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  DB_TOGG



#define _________________QWERTY_L1_________________       KC_Q,     KC_W,     KC_E,     KC_R,     KC_T
#define _________________QWERTY_L2_________________       KC_A,     KC_S,     KC_D,     KC_F,     KC_G
#define _________________QWERTY_L3_________________       KC_Z,     KC_X,     KC_C,     KC_V,     KC_B

#define _________________QWERTY_R1_________________       KC_Y,     KC_U,     KC_I,     KC_O,     KC_P
#define _________________QWERTY_R2_________________       KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN
#define _________________QWERTY_R3_________________       KC_N,     KC_M,     LP_COMM,  LP_DOT,   LP_SLSH



#define _________________AZERTY_L1_________________       FR_Q,     FR_W,     FR_F,     FR_P,     FR_B
#define _______________AZERTY_HRM_L2_______________       FR_HRM_A, FR_HRM_R, FR_HRM_S, FR_HRM_T, FR_G
#define _________________AZERTY_L3_________________       FR_Z,     FR_X,     FR_C,     FR_D,     FR_V

#define _________________AZERTY_R1_________________       FR_J,     FR_L,     FR_U,     FR_Y,     FR_SCLN
#define _______________AZERTY_HRM_R2_______________       FR_M,     FR_HRM_N, FR_HRM_E, FR_HRM_I, FR_HRM_O
#define _________________AZERTY_R3_________________       FR_K,     FR_H,     LP_COMM,  LP_DOT,   LP_SLSH


#define _________________FR_SYMB_L1________________       LPS_GT,   FR_7,     FR_8,     FR_9,     FR_AT
#define _________________FR_SYMB_L2________________       HRM_DOT,  FR_HRM_1, FR_HRM_2, FR_HRM_3, FR_HASH
#define _________________FR_SYMB_L3________________       LPS_LT,   FR_4,     FR_5,     FR_6,     LP_EXLM

#define _________________FR_SYMB_R1________________       FR_DLR,   LP_LPRN,  LP_RPRN,  K_CBR,    FR_RCBR
#define _________________FR_SYMB_R2________________       LPS_EQL,  FR_HRM_MINS,HRM_PLUS,HRM_SLSH,HRM_ASTR
#define _________________FR_SYMB_R3________________       LPS_AMP,  FR_UNDS,  LP_LBRC,  FR_RBRC,  LPS_PIPE


#define ________________FR_ALTGR_L1________________       FR_GRV,   _______,  FR_CIRC,  FR_DIAE,  _______
#define ________________FR_ALTGR_L2________________       FR_AGRV,  _______,  FR_MICR,  _______,  FR_EURO
#define ________________FR_ALTGR_L3________________       _______,  _______,  FR_CCED,  FR_DEG,   FR_PND

#define ________________FR_ALTGR_R1________________       _______,  _______,  _______,  FR_UGRV,  _______
#define ________________FR_ALTGR_R2________________       _______,  FR_EGRV,  FR_EACU,  _______,  _______
#define ________________FR_ALTGR_R3________________       FR_CURR,  _______,  _______,  _______,  _______
