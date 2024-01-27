
#ifndef _KEYMAP_ALICE69_H_
#define _KEYMAP_ALICE69_H_

#include QMK_KEYBOARD_H

#include "keymap_french.h"

#include "layers.h"
#include "custom_keys.h"
#include "bluetooth_keys.h"

#ifndef MACRO_ANSI_69
#define LAYOUT_69_auto LAYOUT_69_ansi
#else
#define LAYOUT_69_auto LAYOUT_ansi_69
#endif

#ifndef INVERTED_ENCODER
#define ENCODER_AUTO ENCODER_CCW_CW
#else
#define ENCODER_AUTO(a,b) ENCODER_CCW_CW(b,a)
#endif

// KC_CAPS becomes Esc/Ctrl
//#define ESC_CTL LCTL_T(KC_ESC)
#define ESC_CTL KC_NO     // disabled while I get used to the layout
// or EXTEND
//#define L_EXTEND LT(0, KC_NO)
#define L_EXTEND OSL(EXTEND)
#define L_NAV OSL(NAV)
#define L_AZSYM OSL(AZ_SYM)

// KC_RALT becomes Compose/RAlt with Compose set to RWin in Gnome
#define CMP_RALT RALT_T(KC_RWIN)

// Shortcut for Crtl+Gui, Ctrl+Shift, Ctrl+Alt
#define CG(kc) (QK_LCTL | QK_LGUI | (kc))
#define CS(kc) (QK_LCTL | QK_LSFT | (kc))
#define CA(kc) (QK_LCTL | QK_LALT | (kc))

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

// tmux key
#define K_TMUX LCTL(KC_A)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#ifdef AZERTY_LAYER_ENABLE
    [AZERTY] = LAYOUT_69_auto(      // the host is set to AZERTY
        KC_ESC,  FR_1,     FR_2,     FR_3,    FR_4,    FR_5,    FR_6,     FR_7,    FR_8,    FR_9,    FR_0,     FR_MINS,  FR_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  FR_Q,     FR_W,     FR_F,    FR_P,    FR_B,    FR_J,     FR_L,    FR_U,    FR_Y,    FR_SCLN,  KC_LBRC,  KC_RBRC,  FR_BSLS,          KC_DEL,
        L_EXTEND,FR_A,     FR_R,     FR_S,    FR_T,    FR_G,              FR_M,    FR_N,    FR_E,    FR_I,     FR_O,     FR_QUOT,  KC_ENT,           KC_HOME,
        OSM_LSFT,          FR_X,     FR_C,    FR_D,    FR_V,    FR_Z,     KC_RALT, FR_K,    FR_H,    FR_COMM,  FR_DOT,   FR_SLSH,  OSM_RSFT,KC_UP,
        OSM_LCTL,KC_LWIN,  KC_LALT,           KC_LSFT,          L_NAV,    L_EXTEND,         KC_SPC,            L_AZSYM,            KC_LEFT, KC_DOWN, KC_RGHT),
#endif

    [COLEMAK] = LAYOUT_69_auto(     // the host is set to QWERTY
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          XXXXXXX,
        KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_B,    KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_PGUP,
        L_EXTEND,KC_A,     KC_R,     KC_S,    KC_T,    KC_G,              KC_M,    KC_N,    KC_E,    KC_I,     KC_O,     KC_QUOT,  KC_ENT,           KC_PGDN,
        OSM_LSFT,          KC_X,     KC_C,    KC_D,    KC_V,    KC_Z,     K_TMUX,  KC_K,    KC_H,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM_RSFT,KC_UP,
        OSM_LCTL,KC_LWIN,  KC_LALT,           KC_LSFT,          L_NAV,    L_EXTEND,         KC_SPC,            CMP_RALT,           KC_LEFT, KC_DOWN, KC_RGHT),

    [EXTEND] = LAYOUT_69_auto(
        KC_NO,   KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL,           KC_MUTE,
        A(KC_TAB),XXXXXXX, C(KC_W),  C(KC_F), XXXXXXX, XXXXXXX, KC_HOME,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,   XXXXXXX,  XXXXXXX,  CC_ELOCK,         KC_DEL,
        XXXXXXX, OSM_LALT, KC_ACL0,  OSM_LSFT,OSM_LCTL,KC_LWIN,           KC_END,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_BSPC,  KC_GRV,   _______,          KC_INS,
        _______,           C(KC_X),  C(KC_C), XXXXXXX, C(KC_V), C(KC_Z),  XXXXXXX, KC_TAB,  KS_AHOM, KS_DPW,   XXXXXXX,  XXXXXXX,  CW_TOGG, KC_MS_U,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            KC_MS_L, KC_MS_D, KC_MS_R),

    [NAV] = LAYOUT_69_auto(
        KC_NO,   A(KC_1),  A(KC_2),  A(KC_3), A(KC_4), A(KC_5), A(KC_6),  A(KC_7), A(KC_8), A(KC_9), A(KC_0),  KC_F11,   KC_F12,   _______,          _______,
        _______, _______,  CG(KC_W), CG(KC_F),CA(KC_P),CG(KC_B),_______,  CG(KC_L),_______, CG(KC_Y),_______,  CA(KC_LBRC),CA(KC_RBRC),_______,      KC_HOME,
        TG(NUMPAD),_______,_______,  CG(KC_S),CG(KC_T),_______,           _______, G(KC_F1),G(KC_F2),G(KC_F3), G(KC_F4), _______,  _______,          KC_END,
        _______,           _______,  CS(KC_C),_______, CS(KC_V),CG(KC_Z), _______, _______, _______, CS(KC_PGUP),CS(KC_PGDN), _______,  KC_CAPS, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [NUMPAD] = LAYOUT_69_auto(
        TG(NUMPAD),_______, _______,  _______, _______,  _______, _______,  KC_P7,   KC_P8,   KC_P9,   _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______, _______,  _______, _______,  KC_P4,   KC_P5,   KC_P6,   _______,  _______,  _______,  _______,          _______,
        L_EXTEND, _______,  _______,  _______, _______,  _______,           _______, KC_P1,   KC_P2,   KC_P3,    _______,  _______,  _______,          _______,
        _______,            _______,  _______, _______,  _______, KC_NUM,   _______, KC_COMM, KC_P0,   KC_P0,    KC_PDOT,  _______,  _______, _______,
        _______,  _______,  _______,           _______,           L_NAV,    L_EXTEND,         _______,           _______,            _______, _______, _______),

    [SYSTEM] = LAYOUT_69_auto(
#ifdef BLUETOOTH_KEY_CONTROL
        _______, KC_MUTE,  KC_VOLD,  KC_VOLU, KC_F20,  KC_BRID, KC_BRIU,  CC_DISP, _______, _______, _______,  _______,  _______,  CC_RGBRT,         CC_RGBTG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          QK_BOOT,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,           _______, _______, _______, _______,  _______,  _______,  _______,          DB_TOGG,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, BAT_LVL, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______
#else
        _______, KC_MUTE,  KC_VOLD,  KC_VOLU, KC_F20,  KC_BRID, KC_BRIU,  CC_DISP, _______, _______, _______,  _______,  _______,  CC_RGBRT,         CC_RGBTG,
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          QK_BOOT,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,           _______, _______, _______, _______,  _______,  _______,  _______,          DB_TOGG,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______
#endif
        ),

#ifdef AZERTY_LAYER_ENABLE
    [AZ_SYM] = LAYOUT_69_auto(
        _______,  _______,  FR_SUP2,  _______, FR_PND,   FR_EURO, FR_CIRC,  _______, _______, _______, FR_DEG,   _______,  _______,  _______,          _______,
        _______,  FR_GRV,   FR_TILD,  _______, _______,  _______, _______,  _______, _______, FR_UGRV, FR_DIAE,  _______,  _______,  FR_GRV,           _______,
        _______,  FR_AGRV,  _______,  FR_SECT, _______,  FR_EGRV,           FR_MICR, _______, FR_EACU, _______,  _______,  _______,  _______,          _______,
        _______,            _______,  _______, FR_CURR,  _______, _______,  _______, _______, _______, FR_CCED,  _______,  _______,  _______, _______,
        _______,  _______,  _______,           _______,           _______,  _______,          _______,           _______,            _______, _______, _______),
#endif

/*
    [MODEL] = LAYOUT_69_auto(
        _______,  _______,  _______,  _______, _______,  _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______, _______,  _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______, _______,  _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,            _______,  _______, _______,  _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______,  _______,  _______,           _______,           _______,  _______,          _______,           _______,            _______, _______, _______),
*/
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
#ifdef AZERTY_LAYER_ENABLE
    [AZERTY]   = { ENCODER_AUTO(KC_VOLD, KC_VOLU)},
#endif
    [COLEMAK]  = { ENCODER_AUTO(KC_LEFT, KC_RIGHT)},
    [EXTEND]   = { ENCODER_AUTO(KC_VOLD, KC_VOLU)},
    [NAV]      = { ENCODER_AUTO(KC_BRID, KC_BRIU)},
    [NUMPAD]   = { ENCODER_AUTO(KC_VOLD, KC_VOLU)},
    [SYSTEM]   = { ENCODER_AUTO(RGB_VAD, RGB_VAI)},
#ifdef AZERTY_LAYER_ENABLE
    [AZ_SYM]   = { ENCODER_AUTO(KC_VOLD, KC_VOLU)},
#endif
};
#endif // ENCODER_MAP_ENABLE

#endif