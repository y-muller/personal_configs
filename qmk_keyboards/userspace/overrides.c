
#include QMK_KEYBOARD_H
#ifdef AZERTY_LAYER_ENABLE
#include "keymap_french.h"
#endif
#include "layers_alice69.h"

// Key overrides - mouse scroll wheel on Shift, mouse buttons on Control
const key_override_t left_scrollwheel_override   = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_L, KC_WH_L, (1<<EXTEND | 1<<NAV));
const key_override_t right_scrollwheel_override  = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_R, KC_WH_R, (1<<EXTEND | 1<<NAV));
const key_override_t up_scrollwheel_override     = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_U, KC_WH_U, (1<<EXTEND | 1<<NAV));
const key_override_t down_scrollwheel_override   = ko_make_with_layers(MOD_MASK_SHIFT, KC_MS_D, KC_WH_D, (1<<EXTEND | 1<<NAV));
const key_override_t left_mousebutton_override   = ko_make_with_layers(MOD_MASK_ALT,   KC_MS_L, KC_BTN1, (1<<EXTEND | 1<<NAV));
const key_override_t right_mousebutton_override  = ko_make_with_layers(MOD_MASK_ALT,   KC_MS_R, KC_BTN2, (1<<EXTEND | 1<<NAV));
const key_override_t middle_mousebutton_override = ko_make_with_layers(MOD_MASK_ALT,   KC_MS_D, KC_BTN3, (1<<EXTEND | 1<<NAV));

// tilde in its usual place with Shift+Esc, backtick with AltGr+Esc 
const key_override_t tilde_override    = ko_make_with_layers(MOD_MASK_SHIFT,   KC_ESC,  KC_TILDE, (1 << COLEMAK));
const key_override_t backtick_override = ko_make_with_layers(MOD_BIT(KC_RIGHT_ALT),   KC_ESC,  KC_GRV, (1 << COLEMAK));

#ifdef AZERTY_LAYER_ENABLE
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
#endif

const key_override_t **key_overrides = (const key_override_t *[]){
    &left_scrollwheel_override,
    &right_scrollwheel_override,
    &up_scrollwheel_override,
    &down_scrollwheel_override,
    &left_mousebutton_override,
    &right_mousebutton_override,
    &middle_mousebutton_override,
    &tilde_override,
    &backtick_override,
#ifdef AZERTY_LAYER_ENABLE
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
#endif
    NULL // Null terminate the array of overrides!
};
