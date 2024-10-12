
#include QMK_KEYBOARD_H

// clang-format off
#include "keymap_corne46.h"

#include "overrides.h"

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN(td_bootloader),
    [TD_EECLR] = ACTION_TAP_DANCE_FN(td_clear_eeprom),
    [TD_CBR] = ACTION_TAP_DANCE_FN_ADVANCED(td_curly_braces_each, td_curly_braces_finished, td_curly_braces_reset),
//    [TD_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(td_leader_each, td_leader_finished, NULL),
//    [TD_BSLS] = ACTION_TAP_DANCE_FN_ADVANCED(td_bsls_each, td_bsls_finished, td_bsls_reset),
#ifdef LEADER_ENABLE
    [TD_RSFT_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(/*td_rsft_lead_each*/ NULL, td_rsft_lead_finished, td_rsft_lead_reset),
#endif
    [TD_ALTGR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_altgr_finished, td_altgr_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset),
//    [TD_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_tmux_finished, td_tmux_reset)
};
