
#pragma once

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_INTERRUPTED,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TD_BOOT,
    TD_EECLR,
    TD_LEAD,
    TD_BSLS,
    TD_RSFT_LEAD,
    TD_CAPS,
    TD_ALTGR,
    TD_TMUX
};

td_state_t cur_dance(tap_dance_state_t *state);

void td_bootloader(tap_dance_state_t *state, void *user_data);
void td_clear_eeprom(tap_dance_state_t *state, void *user_data);
void td_rsft_lead_finished(tap_dance_state_t *state, void *user_data);
void td_rsft_lead_reset(tap_dance_state_t *state, void *user_data);
void td_altgr_finished(tap_dance_state_t *state, void *user_data);
void td_altgr_reset(tap_dance_state_t *state, void *user_data);
void td_caps_finished(tap_dance_state_t *state, void *user_data);
void td_caps_reset(tap_dance_state_t *state, void *user_data);
void td_tmux_finished(tap_dance_state_t *state, void *user_data);
void td_tmux_reset(tap_dance_state_t *state, void *user_data);


