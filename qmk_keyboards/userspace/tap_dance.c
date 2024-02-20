
#if defined( TAP_DANCE_ENABLE )

#include QMK_KEYBOARD_H

#include "tap_dance.h"
#include "layers.h"

bool tmux_lock = false;

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


void td_leader_each(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        uint8_t mod = get_mods();
        uint8_t osm = get_oneshot_mods() ;
        if (mod & MOD_MASK_SHIFT || osm & MOD_MASK_SHIFT ) {
            tap_code16( S(KC_BSLS) );
            reset_tap_dance(state);
        } else if (mod & MOD_BIT(KC_RALT) || osm & MOD_BIT(KC_RALT) ) {
            tap_code( KC_BSLS );
            reset_tap_dance(state);
        }
    } else if (state->count > 1) {
        tap_code( KC_BSLS );
    }
}

void td_leader_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        leader_start();
    }
}


// Create an instance of 'td_tap_t' for the 'tmux' tap dance.
static td_tap_t ext_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

bool help_is_shown = false;

void td_tmux_finished(tap_dance_state_t *state, void *user_data) {
    ext_tap_state.state = cur_dance(state);
    switch (ext_tap_state.state) {
        case TD_SINGLE_TAP:
            if (!leader_sequence_active()) {
                register_code( KC_LCTL );
                tap_code( KC_A );
                unregister_code( KC_LCTL );
            }
            break;
        case TD_SINGLE_HOLD:
            uint8_t mod_shift = get_mods() & MOD_MASK_SHIFT;
            uint8_t osm_shift = get_oneshot_mods() & MOD_MASK_SHIFT;
            if (mod_shift || osm_shift ) {
                //
                // Send keycode for run-or-raise to display layout help
                //
                help_is_shown = true;
                switch (get_highest_layer(layer_state)) {
                    case 0:
                        tap_code( KC_LNG1 );
                        break;
                    case EXTEND:
                        tap_code( KC_LNG2 );
                        break;
                    case NAV:
                        tap_code( KC_LNG3 );
                        break;
                    case SYSTEM:
                        tap_code( KC_LNG4 );
                        break;
                    case NUMPAD:
                        tap_code( KC_LNG5 );
                        break;
                }
            } else {
                //
                // TMUX mode, handled in process_record_user
                // resets at the end of the tap dance
                //
                tmux_lock = true;
            }
            break;
        case TD_DOUBLE_TAP:
            leader_start();
            break;
        case TD_DOUBLE_HOLD:
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default: break;
    }
}

void td_tmux_reset(tap_dance_state_t *state, void *user_data) {
    switch (ext_tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            if (help_is_shown) {
                // help key is released
                help_is_shown = false;
                tap_code16( C(KC_LNG1) );
            }
            // cancel TMUX mode
            tmux_lock = false;
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default: break;
    }
    ext_tap_state.state = TD_NONE;
}

void td_bootloader(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
        reset_tap_dance(state);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN(td_bootloader),
    [TD_LEAD] = ACTION_TAP_DANCE_FN_ADVANCED(td_leader_each, td_leader_finished, NULL),
    [TD_TMUX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_tmux_finished, td_tmux_reset)
};

#endif  // USER_CONFIG_ENABLE
