
#pragma once

#include "keymap_french.h"

enum combos {
    DF_MEDIA,
    DF_MEDIA_MO,
    M_MEDIA_UNL,
    DF_LEADER,
    DF_SAVE,
    DF_COPY,
    DF_PASTE,
    DF_CUT,
    DF_BACKSP,

    DF_UNDO,
    DF_VIMCMD,
    DF_MINUS,
    DF_UNDS,
    DF_QUOTE,
    DF_DQUOTE,
    DF_COLON,
    DF_SCOL,
    DF_EXCLAM,
    DF_Q,
    //DF_ENTER,

    // Symbols
    S_PERCENT,
    S_BSLASH,
    S_QUOTE,
    S_DQUOTE,

#ifdef SYSTEM_LAYER_COMBO
    SYSLAYER,
    SYSLAYER2,
#endif

//  Help
    HLP_MAIN,
    HLP_EXTEND,
    HLP_NAV,
    HLP_MEDIA,
    HLP_SYMBS,
    HLP_NUMPAD,
    HLP_SYST,
};

uint8_t combo_ref_from_layer(uint8_t layer){
    switch (get_highest_layer(layer_state)){
        case COLEMAKH: return COLEMAK;
#ifdef AZERTY_LAYER_ENABLE
        case AZERTY: return COLEMAK;
        case FR_SYMB: return SYMBOLS;
#endif
    }
    return layer;  // important if default is not in case.
}

const uint16_t PROGMEM media_combo[] = {ESC_MD, KC_Q, COMBO_END};               // Lock Media layer
const uint16_t PROGMEM media_unl_combo[] = {KC_ESC, KC_MUTE, COMBO_END};        // Unlock Media layer, same position as above on Media layer
const uint16_t PROGMEM media_mo_combo[] = {KC_SCLN,  KC_BSPC, COMBO_END};       // Momentary Media layer
const uint16_t PROGMEM leader_combo[] = {KC_H, LP_COMM, COMBO_END};             // Leader key
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM save_combo[] = {KC_W, KC_F, COMBO_END};                  // Save (Write File)
const uint16_t PROGMEM vimcmd_combo[] = {KC_L, KC_U, COMBO_END};                // vim command
const uint16_t PROGMEM minus_combo[] = {KC_M, KC_N, COMBO_END};                 // Minus
const uint16_t PROGMEM underscore_combo[] = {KC_N, KC_H, COMBO_END};            // Underscore
const uint16_t PROGMEM quote_combo[] = {KC_U, KC_E, COMBO_END};                 // Quote
const uint16_t PROGMEM doublequote_combo[] = {KC_Y, KC_I, COMBO_END};           // Double quote
const uint16_t PROGMEM colon_combo[] = {KC_T, KC_D, COMBO_END};                 // Colon
const uint16_t PROGMEM semicolon_combo[] = {KC_S, KC_C, COMBO_END};             // Semi-colon
const uint16_t PROGMEM exclam_combo[] = {KC_O, LP_SLSH, COMBO_END};             // Exclamation mark
const uint16_t PROGMEM backspace_combo[] = {KC_M, KC_K, COMBO_END};             // Backspace
const uint16_t PROGMEM q_combo[] = {KC_A, KC_Z, COMBO_END};                     // Backspace
//const uint16_t PROGMEM enter_combo[] = {KC_N, KC_L, COMBO_END};                 // Enter

// Combos on Symbols layer
const uint16_t PROGMEM percent_symb_combo[] = {KC_DLR, LPS_EQL, COMBO_END};     // percent
const uint16_t PROGMEM bsls_symb_combo[] = {HRM_SLSH, KC_RBRC, COMBO_END};      // backslash
const uint16_t PROGMEM quote_symb_combo[] = {LP_RPRN, HRM_PLUS, COMBO_END};     // Quote
const uint16_t PROGMEM dquote_symb_combo[] = {LP_LCBR, HRM_SLSH, COMBO_END};    // Double quote

#ifdef SYSTEM_LAYER_COMBO
const uint16_t PROGMEM system_layer_combo[] = {CAPS_EXT, K_SYMBS, COMBO_END};   // System layer
const uint16_t PROGMEM system_layer_combo2[] = {KC_ACL0, KC_HOME, COMBO_END};   // System layer from MEDIA
#endif

// Help combos for each layer, in same position
// consider COMBO_ONLY_FROM_LAYER to avoid duplication
//const uint16_t PROGMEM help_combo[] = {L_NAV, CAPS_EXT, COMBO_END};           // Help - work in most layers
const uint16_t PROGMEM help_main_combo[] = {KC_D, KC_H, COMBO_END};             // Help for main layer
const uint16_t PROGMEM help_extend_combo[] = {C(KC_V), KC_TAB, COMBO_END};      // Help for EXTEND layer
const uint16_t PROGMEM help_nav_combo[] = {CS(KC_V), CC_SRCN, COMBO_END};       // Help for NAV layer
const uint16_t PROGMEM help_media_combo[] = {KC_MNXT, KC_BTN3, COMBO_END};      // Help for MEDIA layer
const uint16_t PROGMEM help_symbols_combo[] = {KC_6, KC_UNDS, COMBO_END};       // Help for SYMBOLS layer
//const uint16_t PROGMEM help_numpad_combo[] = {KC_RPRN, KC_1, COMBO_END};      // Help for NUMPAD layer
const uint16_t PROGMEM help_numpad_combo[] = { KC_3, LP_LPRN, COMBO_END};       // Help for NUMPAD layer
const uint16_t PROGMEM help_system_combo[] = {KC_F6, RGB_VAD, COMBO_END};       // Help for SYSTEM layer

combo_t key_combos[] = {
    [DF_MEDIA] = COMBO(media_combo, C_MEDIA),
    [DF_MEDIA_MO] = COMBO(media_mo_combo, C_MEDIA_MO),
    [M_MEDIA_UNL] = COMBO(media_unl_combo, C_MEDIA),
    [DF_LEADER] = COMBO(leader_combo, QK_LEAD),
    [DF_SAVE] = COMBO(save_combo, C(KC_S)),
    [DF_COPY] = COMBO(copy_combo, C(KC_C)),
    [DF_PASTE] = COMBO(paste_combo, C(KC_V)),
    [DF_CUT] = COMBO(cut_combo, C(KC_X)),
    [DF_UNDO] = COMBO(undo_combo, C_UNDO),                     // Needs language-aware handling
    [DF_VIMCMD] = COMBO(vimcmd_combo, C_VIMCMD),                 // Needs language-aware handling
    [DF_MINUS] = COMBO(minus_combo,  C_MINS),                   // Needs language-aware handling
    [DF_UNDS] = COMBO(underscore_combo, C_UNDS),               // Needs language-aware handling
    [DF_QUOTE] = COMBO(quote_combo, C_QUOT),                    // Needs language-aware handling
    [DF_DQUOTE] = COMBO(doublequote_combo, C_DQUO),              // Needs language-aware handling
    [DF_COLON] = COMBO(colon_combo, C_COLN),                    // Needs language-aware handling
    [DF_SCOL] = COMBO(semicolon_combo, C_SCLN),                // Needs language-aware handling
    [DF_EXCLAM] = COMBO(exclam_combo, C_EXLM),                   // Needs language-aware handling
    [DF_BACKSP] = COMBO(q_combo, KC_Q),
    [DF_BACKSP] = COMBO(backspace_combo, KC_BSPC),
    [DF_Q] = COMBO(q_combo, KC_Q),
    //[DF_ENTER] = COMBO(enter_combo, KC_ENT),

// Symbols
    [S_PERCENT] = COMBO(percent_symb_combo, C_PERC),             // Needs language-aware handling
    [S_BSLASH] = COMBO(bsls_symb_combo, C_BSLS),                // Needs language-aware handling
    [S_QUOTE] = COMBO(quote_symb_combo, C_QUOT),               // Same as on base layer
    [S_DQUOTE] = COMBO(dquote_symb_combo, C_DQUO),              // Same as on base layer

#ifdef SYSTEM_LAYER_COMBO
    [SYSLAYER] = COMBO(system_layer_combo, C_SYST),
    [SYSLAYER2] = COMBO(system_layer_combo2, C_SYST),
#endif

//  Help
    [HLP_MAIN] = COMBO(help_main_combo, C_HELP),
    [HLP_EXTEND] = COMBO(help_extend_combo, C_HELP),
    [HLP_NAV] = COMBO(help_nav_combo, C_HELP),
    [HLP_MEDIA] = COMBO(help_media_combo, C_HELP),
    [HLP_SYMBS] = COMBO(help_symbols_combo, C_HELP),
    [HLP_NUMPAD] = COMBO(help_numpad_combo, C_HELP),
    [HLP_SYST] = COMBO(help_system_combo, C_HELP),

};
