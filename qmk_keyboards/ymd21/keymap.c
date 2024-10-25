
#include QMK_KEYBOARD_H

// clang-format off


tap_dance_action_t tap_dance_actions[] = {
//    [TD_BOOT] = ACTION_TAP_DANCE_FN(td_bootloader),
//    [TD_EECLR] = ACTION_TAP_DANCE_FN(td_clear_eeprom),
//    [TD_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(td_leader_each, td_leader_finished, NULL),
};

enum layers{
    NUMPAD,
    LAYER2,
    LAYER3,
    AUDIO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NUMPAD] = LAYOUT_ortho_6x4(
        DF(0),      DF(1),      DF(2),      DF(3),
        KC_TAB,     KC_NUM,     KC_PSLS,    KC_PAST,
        KC_P7,      KC_P8,      KC_P9,      KC_PMNS,
        KC_P1,      KC_P2,      KC_P3,      KC_PPLS,
        KC_P4,      KC_P5,      KC_P6,      KC_PENT,
        KC_P0,      KC_P0,      KC_PDOT,    KC_BSPC
    ),

    [1] = LAYOUT_ortho_6x4(
        DF(0),      DF(1),      DF(2),      DF(3),
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),

    [2] = LAYOUT_ortho_6x4(
        DF(0),      DF(1),      DF(2),      DF(3),
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),

    [AUDIO] = LAYOUT_ortho_6x4(
        DF(0),      DF(1),      DF(2),      DF(3),
        KC_MPLY,    _______,    _______,    KC_MUTE,
        KC_MSTP,    _______,    _______,    KC_VOLD,
        KC_MNXT,    KC_MPRV,    _______,    KC_VOLU,
        S(KC_MNXT), S(KC_MPRV), S(KC_MSTP), S(KC_VOLD),
        S(KC_MPLY), _______,    S(KC_MPRV), S(KC_VOLU)
    ),

};


// AVR optimisations
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif