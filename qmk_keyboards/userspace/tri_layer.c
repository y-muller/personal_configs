
#include QMK_KEYBOARD_H

#ifdef CORNE_FEATURES
#include "layers_corne.h"
#elifdef ORTHO_FEATURES
#include "layers_ortho47.h"
#else
#include "layers_alice69.h"
#endif

bool trilayer_system_state = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef CORNE_FEATURES
    int first_layer = EXTEND;
    int second_layer = SYMBOLS;
    #elifdef ORTHO_FEATURES
    int first_layer = NUMPAD;
    int second_layer = NAV;
    #else
    int first_layer = EXTEND;
    int second_layer = NAV;
    #endif
    bool first_layer_is_off = ((state & (1<<first_layer)) == 0);
    bool second_layer_is_off = ((state & (1<<second_layer)) == 0);
    //uprintf("layer_state_set_user: state:%d previous=%d extend=%d nav=%d\n", state, trilayer_system_state, !first_layer_is_off, !second_layer_is_off);
    if (trilayer_system_state && (first_layer_is_off || second_layer_is_off)) {
        //uprintf("  layer_state_set_user: system not on anymore\n");
        // System layer was on but not anymore, turn off the other 2 layers
        state = state & ~(1<<first_layer);
        state = state & ~(1<<second_layer);
        state = state & ~(1<<SYSTEM);
    } else {
        //uprintf("  layer_state_set_user: updating tri-layer state\n");
        state = update_tri_layer_state(state, first_layer, second_layer, SYSTEM);
    }
    trilayer_system_state = ((state & (1<<SYSTEM)) != 0);
    //uprintf("  layer_state_set_user: tri-layer state=%d\n", trilayer_system_state);
    return state;
}

