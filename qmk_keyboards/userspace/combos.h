
#ifndef _COMBOS_H_
#define _COMBOS_H_

// RWIN (Super) as Left Alt + Nav

const uint16_t PROGMEM media_combo[] = {ESC_MD, KC_Q, COMBO_END};               // Lock Media layer
const uint16_t PROGMEM media2_combo[] = {KC_ESC, KC_MUTE, COMBO_END};            // Unlock Media layer, same position as above on Media layer
const uint16_t PROGMEM leader_combo[] = {KC_H, LP_COMM, COMBO_END};             // Leader key
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM save_combo[] = {KC_W, KC_F, COMBO_END};                  // Save (Write File)
const uint16_t PROGMEM vimcmd_combo[] = {KC_L, KC_U, COMBO_END};                // vim command

// Help combos for each layer, in same position
// consider COMBO_ONLY_FROM_LAYER to avoid duplication
//const uint16_t PROGMEM help_combo[] = {L_NAV, CAPS_EXT, COMBO_END};             // Help - work in most layers
const uint16_t PROGMEM help_main_combo[] = {KC_D, KC_H, COMBO_END};             // Help for main layer
const uint16_t PROGMEM help_extend_combo[] = {C(KC_V), KC_TAB, COMBO_END};      // Help for EXTEND layer
const uint16_t PROGMEM help_nav_combo[] = {CS(KC_V), CC_SRCN, COMBO_END};       // Help for NAV layer
const uint16_t PROGMEM help_media_combo[] = {KC_MNXT, KC_BTN3, COMBO_END};      // Help for MEDIA layer
const uint16_t PROGMEM help_symbols_combo[] = {KC_GT, KC_UNDS, COMBO_END};      // Help for SYMBOLS layer
//const uint16_t PROGMEM help_numpad_combo[] = {KC_RPRN, KC_1, COMBO_END};        // Help for NUMPAD layer
const uint16_t PROGMEM help_numpad_combo[] = { KC_3, LP_LPRN, COMBO_END};        // Help for NUMPAD layer
const uint16_t PROGMEM help_system_combo[] = {RGB_SAD, KC_F1, COMBO_END};       // Help for SYSTEM layer

combo_t key_combos[] = {
    COMBO(media_combo, C_MEDIA),
    COMBO(media2_combo, C_MEDIA),
    COMBO(leader_combo, QK_LEAD),
    COMBO(copy_combo, C(KC_C)),
    COMBO(paste_combo, C(KC_V)),
    COMBO(cut_combo, C(KC_X)),
    COMBO(undo_combo, C(KC_Z)),
    COMBO(save_combo, C(KC_S)),
    COMBO(vimcmd_combo, C_VIMCMD),
//    COMBO(help_combo, C_HELP),
    COMBO(help_main_combo, C_HELP),
    COMBO(help_extend_combo, C_HELP),
    COMBO(help_nav_combo, C_HELP),
    COMBO(help_media_combo, C_HELP),
    COMBO(help_symbols_combo, C_HELP),
    COMBO(help_numpad_combo, C_HELP),
    COMBO(help_system_combo, C_HELP),
};

#endif
