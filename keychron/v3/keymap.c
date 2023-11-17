/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
    FR_BASE,
    FR_FN,
    COLEMAK,
    EXTEND,
    NAV,
    SYSTEM
};

enum my_keycodes {
  CC_DISP = SAFE_RANGE, // Thinkpad display switching F7
  CC_MINRGB,            // RGB mostly off, used for indicators
  CC_ELOCK,             // Lock Extend layer
  CC_TEST
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [FR_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_MUTE,  KC_NO,    KC_NO,    RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_A,     KC_Z,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_Q,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_M,     KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_W,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_COMM,  KC_SCLN,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  KC_ROPT,  MO(FR_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [FR_FN] = LAYOUT_tkl_f13_ansi(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     RGB_TOG,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [COLEMAK] = LAYOUT_tkl_f13_ansi(  // Colemak CAW with the host set to US
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_MUTE,  KC_PSCR,  KC_NO,    RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_EQL,   KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_LBRC,  KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_QUOT,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        L_EXTEND, KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_RBRC,  KC_M,     KC_N,     KC_E,     KC_I,     KC_O,               KC_ENT,
        OSM_LSFT,           KC_X,     KC_C,     KC_D,     KC_V,     KC_Z,     KC_SLSH,  KC_K,     KC_H,     KC_COMM,  KC_DOT,             OSM_RSFT,           KC_UP,
        OSM_LCTL, KC_LWIN,  KC_LALT,                                KC_SPC,                                 L_EXTEND, CMP_RALT, L_NAV,    OSM_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT),

/*    [WIN_BASE] = LAYOUT_tkl_f13_ansi(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,  KC_PSCR,  KC_NO,    RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        ESC_CTL,  GUI_A,    ALT_S,    SFT_D,    CTL_F,    KC_G,     KC_H,     CTL_J,    SFT_K,    ALT_L,    GUI_SCLN, KC_QUOT,              KC_ENT,
        SC_LSPO,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              SC_RSPC,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 CMP_RALT, KC_RWIN,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),
*/

    [EXTEND] = LAYOUT_tkl_f13_ansi(
        KC_NO,    G(KC_F1), G(KC_F2), G(KC_F3), G(KC_F4), _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_WH_L,  KC_WH_R,  _______,
        A(KC_GRV),A(KC_1),  A(KC_2),  A(KC_3),  A(KC_4),  A(KC_5),  A(KC_6), _______,   A(KC_7),  A(KC_8),  A(KC_9),  A(KC_0),_______,  _______,  KC_BTN3,  _______,  KC_WH_U,
        A(KC_TAB),KC_ESC,   C(KC_W),  C(KC_F),  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_DEL,   KC_MENU,  CC_ELOCK, KC_BTN1,  KC_BTN2,  KC_WH_D,
        _______,  OSM_LALT, KC_ACL0,  OSM_LSFT, OSM_LCTL, KC_LWIN,  _______,  KC_END,   KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_BSPC,            _______,
        CW_TOGG,            C(KC_X),  C(KC_C),  _______,  C(KC_V),  C(KC_Z),  _______,  _______,  KS_AHOM,  KS_DPW,   _______,            _______,            KC_MS_U,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R),


    [NAV] = LAYOUT_tkl_f13_ansi(
        _______, G(KC_F1),  G(KC_F2),  G(KC_F3),  G(KC_F4),  _______,   _______,   _______,   _______,   _______,    _______,  _______,  _______,  _______,  _______,  TO(SYSTEM),  _______,
        _______, LCA(KC_1), LCA(KC_2), LCA(KC_3), LCA(KC_4), LCA(KC_5), LCA(KC_6), LCA(KC_7), LCA(KC_8), LCA(KC_9), LCA(KC_0),  _______,  _______,  _______,  _______,  _______,  _______,
        _______, _______,   LCG(KC_W), LCG(KC_F), LCA(KC_P), LCG(KC_B),  LCG(KC_Y), _______,   _______,   LCG(KC_O), LCG(KC_Y),  LCA(KC_LBRC),  LCA(KC_RBRC),  KC_BSLS,  _______,  _______,  _______,
        _______, _______,   _______,   LCG(KC_S),   _______,  _______,    _______,   _______,   G(KC_F1),  G(KC_F2),  G(KC_F3),   G(KC_F4),            _______,
        KC_CAPS,            _______,   LCS(KC_C),  _______, LCS(KC_V),  LCG(KC_Z), _______,   _______,   _______,   _______,    _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                             _______,   _______,    _______,  _______,  _______,  _______,  _______),


    [SYSTEM] = LAYOUT_tkl_f13_ansi(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RGB_TOG,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [FR_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FR_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [COLEMAK] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [EXTEND]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [NAV]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [SYSTEM]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif // ENCODER_MAP_ENABLE
