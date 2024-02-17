#include QMK_KEYBOARD_H
#include "custom_keys.h"
#include "tap_dance.h"

void leader_start_user(void) {
    print("leader_start_user\n");
}


void insert_tags( char* opening, char* closing ) {
    send_string( opening );
    send_string( closing );
    for( int i = 0; i < strlen( closing ); i++ ) {
        tap_code( KC_LEFT ); 
    }
}

void wrap_selection_string( char* opening, char* closing ) {
    tap_code16( C(KC_X) );
    send_string( opening );
    tap_code16( C(KC_V) );
    send_string( closing );
}

void leader_end_user(void) {
    print("leader_end_user\n");
    if (leader_sequence_one_key( TD_TMUX )) {
        // cancel leader sequence

    } else if (leader_sequence_two_keys(KC_H, KC_B)) {
        // <B>$</B>   - $ marks the position of the cursor
        insert_tags( "<b>", "</b>" );

    } else if (leader_sequence_two_keys(KC_3, KC_I)) {
        // #include $
        send_string( "#include " );

    } else if (leader_sequence_two_keys(KC_W, KC_QUOT)) {
        wrap_selection_string( "'", "'" );

    } else if (leader_sequence_three_keys(KC_W, KC_QUOT, KC_QUOT)) {
        wrap_selection_string( "\"", "\"" );

    } else if (leader_sequence_two_keys(KC_W, KC_LBRC)) {
        wrap_selection_string( "[", "]" );

    } else if (leader_sequence_two_keys(KC_W, KC_B)) {
        wrap_selection_string( "<b>", "</b>" );

    } else if (leader_sequence_three_keys(KC_W, KC_LBRC, KC_LBRC)) {
        wrap_selection_string( "SS_LSFT(X_LBRC)", "SS_LSFT(X_RBRC)" );

    } else if (leader_sequence_two_keys(KC_W, KC_9)) {
        wrap_selection_string( "(", ")" );

    } else if (leader_sequence_three_keys(KC_W, KC_9, KC_9)) {
        wrap_selection_string( "SS_LSFT(X_9)", "SS_LSFT(X_9)" );

    } else if (leader_sequence_one_key(KC_T)) {
        send_string("Hello xxXXxx !" );
    }
}

