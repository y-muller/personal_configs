
#pragma once

#include QMK_KEYBOARD_H

#ifdef SPLIT_KEYBOARD
#    include "split_sync.h"
#endif // SPLIT_KEYBOARD

void show_layout_help(void);
void close_layout_help(void);

void process_tmux_mode(uint16_t keycode, keyrecord_t *record);
bool process_select_mode(uint16_t keycode, keyrecord_t *record);

typedef union {
    uint64_t raw;
    struct {
        bool     rgb_layer_change     : 1;
        bool     is_overwatch         : 1;
        bool     nuke_switch          : 1;
        bool     swapped_numbers      : 1;
        bool     rgb_matrix_idle_anim : 1;
        bool     reserved1            : 1;
        bool     matrix_scan_print    : 1;
        bool     align_reserved       : 1;
        uint8_t  oled_brightness      : 8;
        bool     oled_lock            : 1;
        bool     enable_acceleration  : 1;
        uint8_t  display_mode         : 2;
        uint8_t  display_logo         : 4;
        bool     clap_trap_enable     : 1;
        uint32_t reserved             : 6;
        bool     check                : 1;
        HSV      painter_hsv;
        uint8_t  reserved2 : 7;
        bool     check1    : 1;
    };
} userspace_config_t;

_Static_assert(sizeof(userspace_config_t) == sizeof(uint64_t), "Userspace EECONFIG out of spec.");

extern userspace_config_t userspace_config;

typedef union {
    uint32_t raw;
    struct {
        bool     audio_enable         : 1;
        bool     audio_clicky_enable  : 1;
        bool     tap_toggling         : 1;
        uint8_t  unicode_mode         : 3;
        bool     swap_hands           : 1;
        bool     host_driver_disabled : 1;
        uint8_t  unicode_typing_mode  : 3;
        bool     is_caps_word         : 1;
        bool     is_leader            : 1;
        bool     is_tmux              : 1;
        uint32_t reserved             : 18;
    };
} user_runtime_config_t;

_Static_assert(sizeof(user_runtime_config_t) == sizeof(uint32_t), "Userspace Runtime config out of spec.");

extern user_runtime_config_t user_state;

bool     is_device_suspended(void);
void     set_is_device_suspended(bool status);
