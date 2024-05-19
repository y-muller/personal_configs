
#ifndef _COMBOS_H_
#define _COMBOS_H_

// RWIN (Super) as Left Alt + Nav

#ifdef ORTHO_FEATURES
const uint16_t PROGMEM rwin_combo[] = {KC_LALT, L_NAV, COMBO_END};
const uint16_t PROGMEM media_combo[] = {TAB_MS, KC_Q, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM select_all_combo[] = {KC_A, KC_V, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM save_combo[] = {KC_W, KC_F, COMBO_END};          // Save (Write File)
#endif

// move the #ifdef inside the array if there are some non-ortho combos
#ifdef ORTHO_FEATURES
combo_t key_combos[] = {
    COMBO(rwin_combo, KC_LWIN),
    COMBO(media_combo, C_MEDIA),
    COMBO(copy_combo, C(KC_C)),
    COMBO(paste_combo, C(KC_V)),
    COMBO(cut_combo, C(KC_Z)),
    COMBO(select_all_combo, C(KC_A)),
    COMBO(undo_combo, C(KC_Z)),
    COMBO(save_combo, C(KC_S)),
};
#endif

#endif
