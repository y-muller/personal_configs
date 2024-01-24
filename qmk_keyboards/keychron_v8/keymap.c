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
#include "rgb_map.h"

enum layers{
    AZERTY,
    AZ_SYM,
    COLEMAK,
    NUMPAD,
    EXTEND,
    NAV,
    SYSTEM,
};

enum my_keycodes {
  CC_DISP = SAFE_RANGE, // Thinkpad display switching F7
  CC_MINRGB,            // RGB mostly off, used for indicators
  CC_ELOCK,             // Lock Extend layer
  CC_ANYK,              // For the extra B
  CC_TEST
};

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

uint8_t one_shot_active_mods = 0;
bool trilayer_system_state = false;

// Key overrides - mouse scroll wheel on Shift, mouse buttons on Control
const key_override_t left_scrollwheel_override   = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_L, KC_WH_L, (1 << EXTEND));
const key_override_t right_scrollwheel_override  = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_R, KC_WH_R, (1 << EXTEND));
const key_override_t up_scrollwheel_override     = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_U, KC_WH_U, (1 << EXTEND));
const key_override_t down_scrollwheel_override   = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_D, KC_WH_D, (1 << EXTEND));
const key_override_t left_mousebutton_override   = ko_make_with_layers(MOD_MASK_ALT,   KC_MS_L, KC_BTN1, (1 << EXTEND));
const key_override_t right_mousebutton_override  = ko_make_with_layers(MOD_MASK_ALT,   KC_MS_R, KC_BTN2, (1 << EXTEND));
const key_override_t middle_mousebutton_override = ko_make_with_layers(MOD_MASK_ALT,   KC_MS_D, KC_BTN3, (1 << EXTEND));
// AZERTY number row and other symbols overrides
const key_override_t fr1_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_1,    FR_EXLM, (1 << AZERTY));
const key_override_t fr2_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_2,    FR_AT, (1 << AZERTY));
const key_override_t fr3_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_3,    FR_HASH, (1 << AZERTY));
const key_override_t fr4_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_4,    FR_DLR, (1 << AZERTY));
const key_override_t fr5_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_5,    FR_PERC, (1 << AZERTY));
const key_override_t fr6_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_6,    FR_PND, (1 << AZERTY));
const key_override_t fr7_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_7,    FR_AMPR, (1 << AZERTY));
const key_override_t fr8_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_8,    FR_ASTR, (1 << AZERTY));
const key_override_t fr9_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_9,    FR_LPRN, (1 << AZERTY));
const key_override_t fr0_override     = ko_make_with_layers(MOD_MASK_SHIFT, FR_0,    FR_RPRN, (1 << AZERTY));
const key_override_t fr_mins_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_MINS, FR_UNDS, (1 << AZERTY));
const key_override_t fr_quot_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_QUOT, FR_DQUO, (1 << AZERTY));
const key_override_t fr_scln_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_SCLN, FR_COLN, (1 << AZERTY));
const key_override_t fr_comm_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_COMM, FR_LABK, (1 << AZERTY));
const key_override_t fr_dot_override =  ko_make_with_layers(MOD_MASK_SHIFT, FR_DOT,  FR_RABK, (1 << AZERTY));
const key_override_t fr_slsh_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_SLSH, FR_QUES, (1 << AZERTY));
const key_override_t fr_lbrc_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_LBRC, FR_LCBR, (1 << AZERTY));
const key_override_t fr_rbrc_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_RBRC, FR_RCBR, (1 << AZERTY));
const key_override_t fr_bsls_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_BSLS, FR_PIPE, (1 << AZERTY));

const key_override_t **key_overrides = (const key_override_t *[]){
    &left_scrollwheel_override,
    &right_scrollwheel_override,
    &up_scrollwheel_override,
    &down_scrollwheel_override,
    &left_mousebutton_override,
    &right_mousebutton_override,
    &middle_mousebutton_override,
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
    NULL // Null terminate the array of overrides!
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [AZERTY] = LAYOUT_69_ansi(      // the host is set to AZERTY
        KC_ESC,  FR_1,     FR_2,     FR_3,    FR_4,    FR_5,    FR_6,     FR_7,    FR_8,    FR_9,    FR_0,     FR_MINS,  FR_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  FR_Q,     FR_W,     FR_F,    FR_P,    FR_B,    FR_J,     FR_L,    FR_U,    FR_Y,    FR_SCLN,  KC_LBRC,  KC_RBRC,  FR_BSLS,          KC_DEL,
        L_EXTEND,FR_A,     FR_R,     FR_S,    FR_T,    FR_G,              FR_M,    FR_N,    FR_E,    FR_I,     FR_O,     FR_QUOT,  KC_ENT,           KC_HOME,
        OSM_LSFT,          FR_X,     FR_C,    FR_D,    FR_V,    FR_Z,     KC_B,    FR_K,    FR_H,    FR_COMM,  FR_DOT,   FR_SLSH,  OSM_RSFT,KC_UP,
        OSM_LCTL,KC_LWIN,  KC_LALT,           KC_LSFT,          L_NAV,    L_EXTEND,         KC_SPC,            L_AZSYM,            KC_LEFT, KC_DOWN, KC_RGHT),

    [COLEMAK] = LAYOUT_69_ansi(     // the host is set to QWERTY
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_F,    KC_P,    KC_B,    KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_PGUP,
        L_EXTEND,KC_A,     KC_R,     KC_S,    KC_T,    KC_G,              KC_M,    KC_N,    KC_E,    KC_I,     KC_O,     KC_QUOT,  KC_ENT,           KC_PGDN,
        ESC_CTL,           KC_X,     KC_C,    KC_D,    KC_V,    KC_Z,     K_TMUX,  KC_K,    KC_H,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM_RSFT,KC_UP,
        OSM_LCTL,KC_LWIN,  KC_LALT,           KC_LSFT,          L_NAV,    L_EXTEND,         KC_SPC,            CMP_RALT,           KC_LEFT, KC_DOWN, KC_RGHT),

    [AZ_SYM] = LAYOUT_69_ansi(
        _______,  _______,  _______,  _______, _______,  FR_EURO, FR_CIRC,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,  _______,  FR_TILD,  _______, _______,  _______, _______,  _______, _______, _______, FR_DIAE,  _______,  _______,  _______,          _______,
        _______,  FR_AGRV,  _______,  _______, _______,  FR_EGRV,           FR_MICR, _______, FR_EACU, _______,  _______,  _______,  _______,          _______,
        _______,            _______,  _______, _______,  _______, _______,  _______, _______, _______, FR_CCED,  _______,  _______,  _______, _______,
        _______,  _______,  _______,           _______,           _______,  _______,          _______,           _______,            _______, _______, _______),

    [NUMPAD] = LAYOUT_69_ansi(
        TG(NUMPAD),_______, _______,  _______, _______,  _______, _______,  KC_P7,   KC_P8,   KC_P9,   _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______, _______,  _______, _______,  KC_P4,   KC_P5,   KC_P6,   _______,  _______,  _______,  _______,          _______,
        L_EXTEND, _______,  _______,  _______, _______,  _______,           _______, KC_P1,   KC_P2,   KC_P3,    _______,  _______,  _______,          _______,
        _______,            _______,  _______, _______,  _______, KC_NUM,   _______, KC_COMM, KC_P0,   KC_P0,    KC_PDOT,  _______,  _______, _______,
        _______,  _______,  _______,           _______,           L_NAV,    L_EXTEND,         _______,           _______,            _______, _______, _______),

    [EXTEND] = LAYOUT_69_ansi(
        KC_NO,   KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL,           _______,
        A(KC_TAB),KC_ESC,  C(KC_W),  C(KC_F), _______, _______, KC_HOME,  KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,   _______,  _______,  CC_ELOCK,         KC_DEL,
        _______, OSM_LALT, KC_ACL0,  OSM_LSFT,OSM_LCTL,KC_LWIN,           KC_END,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_BSPC,  KC_GRV,   _______,          KC_INS,
        _______,           C(KC_X),  C(KC_C), _______, C(KC_V), C(KC_Z),  _______, KC_TAB,  KS_AHOM, KS_DPW,   _______,  _______,  CW_TOGG, KC_MS_U,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            KC_MS_L, KC_MS_D, KC_MS_R),

    [NAV] = LAYOUT_69_ansi(
        KC_ESC,  A(KC_1),  A(KC_2),  A(KC_3), A(KC_4), A(KC_5), A(KC_6),  A(KC_7), A(KC_8), A(KC_9), A(KC_0),  KC_F11,   KC_F12,   _______,          _______,
        _______, _______,  CG(KC_W), CG(KC_F),CA(KC_P),CG(KC_B),_______,  CG(KC_L),_______, CG(KC_Y),_______,  CA(KC_LBRC),CA(KC_RBRC),_______,      KC_HOME,
        TG(NUMPAD),_______,_______,  CG(KC_S),CG(KC_T),_______,           _______, G(KC_F1),G(KC_F2),G(KC_F3), G(KC_F4), _______,  _______,          KC_END,
        _______,           _______,  CS(KC_C),_______, CS(KC_V),CG(KC_Z), _______, _______, _______, CS(KC_PGUP),CS(KC_PGDN), _______,  KC_CAPS, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [SYSTEM] = LAYOUT_69_ansi(
        KC_GRV,  KC_MUTE,  KC_VOLD,  KC_VOLU, KC_F20,  KC_BRID, KC_BRIU,  CC_DISP, _______, _______, _______,  _______,  _______,  _______,          RGB_TOG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, _______, _______, _______,  _______, KC_APP,  KC_SCRL, KC_INS,   KC_PGUP,  _______,  _______,          QK_BOOT,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI,           _______, _______, _______, KC_PSCR,  KC_PGDN,  KC_END,   _______,          DB_TOGG,
        _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD,  _______, BAT_LVL, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

/*
    [MODEL] = LAYOUT_69_ansi(
        _______,  _______,  _______,  _______, _______,  _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______, _______,  _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,  _______,  _______,  _______, _______,  _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,            _______,  _______, _______,  _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______,  _______,  _______,           _______,           _______,  _______,          _______,           _______,            _______, _______, _______),
*/
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [AZERTY]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [COLEMAK]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [EXTEND]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
    [NAV]      = { ENCODER_CCW_CW(_______, _______)},  // external volume control ?
    [NUMPAD]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [SYSTEM]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [AZ_SYM]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif // ENCODER_MAP_ENABLE

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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    // Turn off RGB on undefined layer keys
    if (get_highest_layer(layer_state) > 1) {
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
        rgb_matrix_set_color(LED_SCLN, RGB_RED); // Delete
        rgb_matrix_set_color(LED_O, RGB_RED);    // Backspace
    }

    // Caps lock - turn all the modifier red
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            rgb_matrix_set_color(LED_LIST_MODS[i], RGB_RED);
        }
    }
    else if (is_caps_word_on()) {
        for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
            rgb_matrix_set_color(LED_LIST_MODS[i], RGB_GREEN);
        }
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
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], RGB_YELLOW);
            }
        }
        else if (one_shot_active_mods & MOD_MASK_CTRL)
        {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LIST_MODS); i++) {
                rgb_matrix_set_color(LED_LIST_MODS[i], RGB_ORANGE);
            }
        }
    }

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    bool extend_layer_is_off = ((state & (1<<EXTEND)) == 0);
    bool nav_layer_is_off = ((state & (1<<NAV)) == 0);
    //uprintf("layer_state_set_user: state:%d previous=%d extend=%d nav=%d\n", state, trilayer_system_state, extend_layer_is_off, nav_layer_is_off);
    if (trilayer_system_state && (extend_layer_is_off || nav_layer_is_off)) {
        //uprintf("layer_state_set_user: system not on anymore\n");
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
    //uprintf("Oneshot mods %d\n", mods);
}
