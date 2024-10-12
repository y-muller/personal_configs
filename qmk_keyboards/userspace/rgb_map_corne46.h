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

#ifndef _RGB_MAP_CORNE46_H_
#define _RGB_MAP_CORNE46_H_

#ifdef RGB_MATRIX_ENABLE

/* 
 * ,-----------------------------------------.                  ,-----------------------------------------.
 * |  18  |  17  |  12  |  11  |  4   |  3   |------.    ,------|  26  |  27  |  34  |  35  |  40  |  41  |
 * |------+------+------+------+------+------|  21  |    |  44  |------+------+------+------+------+------|
 * |  19  |  16  |  13  |  10  |  5   |  2   |------|    |------|  25  |  28  |  33  |  36  |  39  |  42  |
 * |------+------+------+------+------+------|  22  |    |  45  |------+------+------+------+------+------|
 * |  20  |  15  |  14  |  9   |  6   |  1   |------'    `------|  24  |  29  |  32  |  37  |  38  |  43  |
 * `------+------+------+------+------+------+----.        ,----+------+------+------+------+------+------'
 *                           |  8   |  7   |  0   |        |  23  |  30  |  31  |
 *                           `--------------------'        `--------------------'
 */

// RGB LED locations
enum led_location_map {
    LED_BR3,
    LED_V,
    LED_G,
    LED_B,

    LED_P,
    LED_T,
    LED_D,
    LED_BR2,

    LED_BR1,
    LED_C,
    LED_S,
    LED_F,

    LED_W,
    LED_R,
    LED_X,

    LED_Z,
    LED_A,
    LED_Q,

    LED_ESC,
    LED_TAB,
    LED_LCTL,

    LED_EX1,
    LED_EX2,
    

    LED_BR4,
    LED_K,
    LED_M,
    LED_J,

    LED_L,
    LED_N,
    LED_H,
    LED_BR5,

    LED_BR6,
    LED_COMM,
    LED_E,
    LED_U,

    LED_Y,
    LED_I,
    LED_DOT,

    LED_SLSH,
    LED_O,
    LED_SCLN,

    LED_BSPC,
    LED_ENT,
    LED_QUOT,

    LED_EX3,
    LED_EX4
};

const uint8_t LED_LIST_MODS[] = {
    LED_BR1,
    LED_BR2,
    LED_BR3,
    LED_BR4,
    LED_BR5,
    LED_BR6
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
    LED_O,
    LED_DOT,
    LED_SLSH,
    LED_QUOT
};

const uint8_t LED_LIST_NUMBERS[] = {
    LED_Q,
    LED_W,
    LED_F,
    LED_P,
    LED_B,
    LED_J,
    LED_L,
    LED_U,
    LED_Y,
    LED_SCLN
};

const uint8_t LED_LIST_FUNC[] = {
    LED_W,
    LED_F,
    LED_P,
    LED_B,
    LED_R,
    LED_S,
    LED_T,
    LED_G,
    LED_X,
    LED_C,
    LED_D,
    LED_V,
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
    LED_L,
    LED_U,
    LED_Y,
    LED_N,
    LED_E,
    LED_I,
    LED_H,
    LED_COMM,
    LED_DOT,
    LED_O
};

const uint8_t LED_LIST_NUMPAD_SYM[] = {
    LED_A,   // MULT.
    LED_R,   // DIV.
    LED_S,   // PLUS
    LED_T,   // MINUS
};

const uint8_t LED_LIST_RGB_SETTINGS[] = {
    LED_L,
    LED_U,
    LED_Y,
    LED_SCLN,
    LED_N,
    LED_E,
    LED_I,
    LED_O,
    LED_H,
    LED_COMM,
    LED_DOT,
    LED_SLSH,
};

const uint8_t _LED_BOOT = LED_ENT;
const uint8_t _LED_DEBUG = LED_QUOT;
const uint8_t _LED_RSTP = LED_Y;

#endif
#endif
