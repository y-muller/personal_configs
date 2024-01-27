
#include QMK_KEYBOARD_H
#include "layers.h"

bool trilayer_system_state = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    bool extend_layer_is_off = ((state & (1<<EXTEND)) == 0);
    bool nav_layer_is_off = ((state & (1<<NAV)) == 0);
    //uprintf("layer_state_set_user: state:%d previous=%d extend=%d nav=%d\n", state, trilayer_system_state, extend_layer_is_off, nav_layer_is_off);
    if (trilayer_system_state && (extend_layer_is_off || nav_layer_is_off)) {
        //uprintf("layer_state_set_user: system not on anymore\n");
        // System layer was on but not anymore, turn off the other 2 layers
        state = state & ~(1<<EXTEND);
        state = state & ~(1<<NAV);
        state = state & ~(1<<SYSTEM);
    } else {
        state = update_tri_layer_state(state, EXTEND, NAV, SYSTEM);
    }
    trilayer_system_state = ((state & (1<<SYSTEM)) != 0);
    return state;
}

