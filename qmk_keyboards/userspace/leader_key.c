#include QMK_KEYBOARD_H
#include "custom_keys.h"
#include "tap_dance.h"
#include "private.h"

//void leader_start_user(void) {
//}


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
    if (leader_sequence_one_key( TD_TMUX )) {
        // cancel leader sequence

    } else if (leader_sequence_one_key( KC_L )) {
        // select entire line, cursor at begining of next line
        tap_code( KC_HOME );
        tap_code( KC_HOME );
        tap_code16( S(KC_DOWN) );

    // ❚ marks the position of the cursor
    } else if (leader_sequence_two_keys(KC_LSFT, KC_B)) {
        // <b>❚</b>
        insert_tags( "<b>", "</b>" );

    } else if (leader_sequence_two_keys(KC_LSFT, KC_L)) {
        // [❚]()
        insert_tags( "[", "]()" );

    } else if (leader_sequence_two_keys(KC_LSFT, KC_I)) {
        // ![❚]()
        insert_tags( "![", "]()" );

    } else if (leader_sequence_two_keys(KC_LSFT, KC_F)) {
        // [^❚]
        insert_tags( "[^", "]" );

    } else if (leader_sequence_one_key(KC_ESC)) {
        // `❚`
        insert_tags( "`", "`" );

    } else if (leader_sequence_two_keys(KC_ESC, KC_ESC)) {
        // ```
        // ❚
        // ```
        insert_tags( "```", "```" );
        tap_code16( S(KC_ENT) );
        tap_code16( S(KC_ENT) );
        tap_code( KC_UP );

    } else if (leader_sequence_one_key(KC_I)) {
        // #include ❚
        send_string( "#include " );

    } else if (leader_sequence_one_key(KC_D)) {
        // #define ❚
        send_string( "#define " );

    } else if (leader_sequence_two_keys(KC_SPC, KC_QUOT)) {
        // 'selection'❚
        wrap_selection_string( "'", "'" );

    } else if (leader_sequence_three_keys(KC_SPC, KC_QUOT, KC_QUOT)) {
        // "selection"❚
        wrap_selection_string( "\"", "\"" );

    } else if (leader_sequence_two_keys(KC_SPC, KC_LBRC)) {
        // [selection]❚
        wrap_selection_string( "[", "]" );

    } else if (leader_sequence_three_keys(KC_SPC, KC_LBRC, KC_LBRC)) {
        // {selection}❚
        wrap_selection_string( "{", "}" );

    } else if (leader_sequence_two_keys(KC_SPC, KC_RBRC)) {
        // [[selection]]❚
        wrap_selection_string( "[[", "]]" );

    } else if (leader_sequence_three_keys(KC_SPC, KC_RBRC, KC_RBRC)) {
        // {{selection}}❚
        wrap_selection_string( "{{", "}}" );

    } else if (leader_sequence_two_keys(KC_SPC, KC_9)) {
        // (selection)❚
        wrap_selection_string( "(", ")" );

    } else if (leader_sequence_two_keys(KC_SPC, KC_0)) {
        // ((selection))❚
        wrap_selection_string( "((", "))" );

    } else if (leader_sequence_two_keys(KC_SPC, KC_8)) {
        // *selection*❚
        wrap_selection_string( "*", "*" );

    } else if (leader_sequence_two_keys(KC_SPC, KC_B)) {
        // <b>selection</b>❚
        wrap_selection_string( "<b>", "</b>" );

    } else if (leader_sequence_two_keys(KC_X, KC_C)) {
        // company name
        send_string( PRIV_COMPANY_NAME );

    } else if (leader_sequence_two_keys(KC_C, KC_X)) {
        // company email
        send_string( PRIV_COMPANY_EMAIL );

    } else if (leader_sequence_two_keys(KC_X, KC_D)) {
        // company domain
        send_string( PRIV_COMPANY_DOMAIN );

    } else if (leader_sequence_two_keys(KC_Y, KC_Y)) {
        // email
        send_string( PRIV_EMAIL );

    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        // domain name 1
        send_string( PRIV_DOMAIN_1 );

    } else if (leader_sequence_two_keys(KC_M, KC_M)) {
        // domain name 2
        send_string( PRIV_DOMAIN_2 );

    }
}

