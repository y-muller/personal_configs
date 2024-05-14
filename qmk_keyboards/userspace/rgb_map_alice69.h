/* Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
   Copyright 2023 y-muller
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _RGB_MAP_ALICE69_H_
#define _RGB_MAP_ALICE69_H_

#ifdef RGB_MATRIX_ENABLE

// Custom colours
#define RGB_GODSPEED 0x00, 0xE4, 0xFF     // color for matching keycaps
#define RGB_NAUTILUS 0x00, 0xA4, 0xA9     // Nautilus Font colors
#define RGB_OFFBLUE 0x00, 0x80, 0xFF      // new color: blue with a hint of green
#define RGB_DKRED 0x28, 0x00, 0x00        // new color: dark red
#define RGB_ORANGE2 0xFF, 0x28, 0x00      // fix: reduced green from 80 to 28
#define RGB_PURPLE2 0x80, 0x00, 0xFF      // fix: increased red from 7A to 80
#define RGB_SPRINGGREEN2 0x00, 0xFF, 0x10 // fix: blue was 80, now 10
#define RGB_YELLOW2 0xFF, 0xB0, 0x00      // fix: green was FF, now B0
#define RGB_OFF RGB_BLACK

// Added by gourdo1 for RGB testing
//                Red   Green Blue          Expected  GMMK Pro result
#define RGB_TEST1 0xFF, 0x00, 0x00   // Q - red       good!
#define RGB_TEST2 0x0F, 0xFF, 0x00   // W - green     good!
#define RGB_TEST3 0x00, 0x00, 0xFF   // E - blue      good!
#define RGB_TEST4 0xFF, 0xB0, 0x00   // R - yellow    slightly green heavy - reduced green LED by quite a bit
#define RGB_TEST5 0x00, 0xFF, 0xFF   // T - cyan      good!
#define RGB_TEST6 0xFF, 0x00, 0xFF   // Y - magenta   very slightly blue heavy?
#define RGB_TEST7 0xFF, 0x28, 0x00   // U - orange    very green heavy at default
#define RGB_TEST8 0xFF, 0x00, 0x80   // I - pink      good!
#define RGB_TEST9 0x80, 0xFF, 0x00   // O - chartreus good!
#define RGB_TEST10 0x00, 0xFF, 0x10  // P - springgrn fixed: was too blue because green LED has blue in it already
#define RGB_TEST11 0x00, 0x80, 0xFF  // A - grn blue  good!
#define RGB_TEST12 0x80, 0x00, 0xFF  // S - purple    good!

// RGB LED locations
enum led_location_map {
    LED_GRV,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_MINS,
    LED_EQL,
    LED_BSPC,
    LED_MUTE, // but there is no LED there!

    LED_TAB,
    LED_Q,
    LED_W,
    LED_F,
    LED_P,
    LED_B,
    LED_J,
    LED_L,
    LED_U,
    LED_Y,
    LED_SCLN,
    LED_RBRC,
    LED_LBRC,
    LED_BLSL,
    LED_DEL,

    LED_CAPS,
    LED_A,
    LED_R,
    LED_S,
    LED_T,
    LED_G,
    LED_M,
    LED_N,
    LED_E,
    LED_I,
    LED_O,
    LED_QUOT,
    LED_ENT,
    LED_HOME,

    LED_LSFT,
    LED_X,
    LED_C,
    LED_D,
    LED_V,
    LED_Z,
    LED_B2,
    LED_K,
    LED_H,
    LED_COMM,
    LED_DOT,
    LED_SLSH,
    LED_RSFT,
    LED_UP,

    LED_LCTL,
    LED_LWIN,
    LED_LALT,
    LED_MSFT,
    LED_FN1,
    LED_FN2,
    LED_SPC,
    LED_RALT,
    LED_LEFT,
    LED_DOWN,
    LED_RIGHT
};

const uint8_t LED_LIST_MODS[] = {
    LED_LSFT,
    LED_LCTL,
    LED_LWIN,
    LED_LALT,
    LED_MSFT,
    LED_FN1,
    LED_FN2,
    LED_RALT,
    LED_RSFT,
    LED_CAPS,   // add CapsLock for more visibility 
    LED_SPC     // space is not a mod but treat is as such for indicators
};

const uint8_t LED_LIST_UNEI[] = {
    LED_U,
    LED_N,
    LED_E,
    LED_I
};

const uint8_t LED_LIST_NEIO[] = {
    LED_N,
    LED_E,
    LED_I,
    LED_O
};

const uint8_t LED_LIST_ARROWS[] = {
    LED_LEFT,
    LED_RIGHT,
    LED_UP,
    LED_DOWN
};

const uint8_t LED_LIST_NUMROW[] = {
    LED_GRV,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_MINS,
    LED_EQL,
    LED_BSPC
};

const uint8_t LED_LIST_LETTERS[] = {
    LED_Q,
    LED_W,
    LED_E,
    LED_R,
    LED_T,
    LED_Y,
    LED_U,
    LED_I,
    LED_O,
    LED_P,
    LED_A,
    LED_S,
    LED_D,
    LED_F,
    LED_G,
    LED_H,
    LED_J,
    LED_K,
    LED_L,
    LED_Z,
    LED_X,
    LED_C,
    LED_V,
    LED_B,
    LED_N,
    LED_M
};

const uint8_t LED_LIST_NUMPAD[] = {
    /*LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,*/
    //LED_EQL,
    LED_7,
    LED_8,
    LED_9,
    LED_L,
    LED_U,
    LED_Y,
    LED_N,
    LED_E,
    LED_I,
    LED_H,
    LED_COMM,
    LED_DOT,
    LED_ENT
};

const uint8_t LED_LIST_NUMPAD_SYM[] = {
    LED_O,      // MULT.
    LED_MINS,   // MINUS
    LED_SLSH,   // DIV.
    LED_SCLN,   // PLUS
};

const uint8_t LED_LIST_RGB_SETTINGS[] = {
    LED_CAPS,
    LED_A,
    LED_R,
    LED_S,
    LED_T,
    LED_G,
    LED_LSFT,
    LED_Z,
    LED_X,
    LED_C,
    LED_D,
    LED_V,
};

const uint8_t _LED_BOOT = LED_DEL;
const uint8_t _LED_DEBUG = LED_HOME;
const uint8_t _LED_RSTP = LED_BSPC;

#endif
#endif
