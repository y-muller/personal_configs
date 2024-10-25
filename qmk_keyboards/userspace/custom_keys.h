
#pragma once

#ifdef CORNE_FEATURES
#  include "layers_corne.h"
#else
#  ifdef ORTHO_FEATURES
#    include "layers_ortho47.h"
#    ifdef MACROPAD_FEATURES
#      include "layers_macropad.h"
#    else
#      include "layers_alice69.h"
#    endif
#  endif
#endif

#define TAB_EXT LT(EXTEND, KC_TAB)
#define TAB_LMOD LT(LMODS, KC_TAB)
#define ENT_RMOD LT(RMODS, KC_TAB)
#define ENT_MD LT(MEDIA, KC_ENT)

#define TAB_CTL  LCTL_T(KC_TAB)
#define GUI_CTL  LCTL_T(KC_LWIN)
#define ALT_QUOT LALT_T(KC_QUOT)
#define SFT_0    SFT_T(KC_0)

#ifdef AZERTY_LAYER_ENABLE
#define FR_ALTQU LALT_T(FR_QUOT)
#endif

#define L_EXTEND OSL(EXTEND)
#define L_NAV OSL(NAV)
//#define L_EXTEND MO(EXTEND)
//#define L_NAV MO(NAV)
//#define L_NUM OSL(NUMPAD)
#define L_AZSYM OSL(AZ_SYM)

// Layers as dual use
#define K_EXT LT(EXTEND, KC_ENT)
#define K_NAV LT(NAV, KC_NO)           // Magic/Repeat on tap
#define K_FUNC LT(SYSTEM, KC_NO)       // Magic/Repeat on tap
//#define BSPC_NUM LT(NUMPAD, KC_BSPC)
#define BSPC_EXT LT(EXTEND, KC_BSPC)

// KC_RALT becomes Compose/RAlt with Compose set to RWin in Gnome
//#define CMP_RALT RALT_T(KC_RWIN)
#define CMP_RALT RWIN_T(KC_RALT)
//#define CMP_RALT KC_RALT

// Rigth Shift is LEAD on tap
#define RS_LEAD TD(TD_RSFT_LEAD)

// Backslash is MACRO layer on hold
//#define BSLS_MC LT(MACRO, KC_BSLS)

// ESC is MEDIA layer on hold
#define ESC_MD LT(MEDIA, KC_ESC)

// Shortcut for Crtl+Gui, Ctrl+Shift, Ctrl+Alt
#define CG(kc) (QK_LCTL | QK_LGUI | (kc))
#define CS(kc) (QK_LCTL | QK_LSFT | (kc))
#define CA(kc) (QK_LCTL | QK_LALT | (kc))

// shortcut for One Shot Mods
#define OSM_LSFT OSM(MOD_LSFT)
#define OSM_RSFT OSM(MOD_RSFT)
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_RCTL OSM(MOD_RCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_RALT OSM(MOD_RALT)

// Home Row Mods
//    Colemak
#define HRM_A LGUI_T(KC_A)
#define HRM_R LALT_T(KC_R)
#define HRM_S LSFT_T(KC_S)
#define HRM_T LCTL_T(KC_T)
#define HRM_N LCTL_T(KC_N)
#define HRM_E LSFT_T(KC_E)
#define HRM_I LALT_T(KC_I)
#define HRM_O LGUI_T(KC_O)
//    Symbols / Numpad
#define HRM_DOT  LGUI_T(KC_DOT)
#define HRM_1 LALT_T(KC_1)
#define HRM_2 LSFT_T(KC_2)
#define HRM_3 LCTL_T(KC_3)
#define HRM_MINS LCTL_T(KC_MINS)
#define HRM_PLUS LSFT_T(KC_PLUS)
#define HRM_SLSH LALT_T(KC_SLSH)
#define HRM_ASTR LGUI_T(KC_ASTR)
//    Qwerty
#ifdef QWERTY_LAYER_ENABLE
#define QW_HRM_A LGUI_T(FR_A)
#define QW_HRM_R LALT_T(FR_R)
#define QW_HRM_S LSFT_T(FR_S)
#define QW_HRM_T LCTL_T(FR_T)
#define QW_HRM_N LCTL_T(FR_N)
#define QW_HRM_E LSFT_T(FR_E)
#define QW_HRM_I LALT_T(FR_I)
#define QW_HRM_O LGUI_T(KC_O)
#endif
//    Azerty
#ifdef AZERTY_LAYER_ENABLE
#define FR_HRM_A LGUI_T(FR_A)
#define FR_HRM_R LALT_T(FR_R)
#define FR_HRM_S LSFT_T(FR_S)
#define FR_HRM_T LCTL_T(FR_T)
#define FR_HRM_N LCTL_T(FR_N)
#define FR_HRM_E LSFT_T(FR_E)
#define FR_HRM_I LALT_T(FR_I)
#define FR_HRM_O LGUI_T(KC_O)
#define FR_SFT_0 SFT_T(FR_0)
//    Azerty Symbols
#define FR_HRM_1 LALT_T(FR_1)
#define FR_HRM_2 LSFT_T(FR_2)
#define FR_HRM_3 LCTL_T(FR_3)
#define FR_HRM_MINS LCTL_T(FR_MINS)
#endif
//    System
#define HRM_VAI LCTL_T(RGB_VAI)
#define HRM_HUI LSFT_T(RGB_HUI)
#define HRM_SAI LALT_T(RGB_SAI)
#define HRM_SPI LGUI_T(RGB_SPI)
//    Media


// Layout change keys
#define DF_CLMK  DF(COLEMAK)
#define DF_CLMKH DF(COLEMAKH)
#define DF_QWERT DF(QWERTY)
#ifdef CURSOR_LAYER
#define TG_CURSR TG(CURSOR)
#endif

// Tabs left and right
#define K_TAB_L CA(KC_PGUP)
#define K_TAB_R CA(KC_PGDN)

// Delete Previous Word (Ctrl+Backspace)
#define KS_DPW LCTL(KC_BSPC)
// Alt+Home (real Home for CodeLite: start of line)
#define KS_AHOM A(KC_HOME)

// TMUX key is a tap dance with HELP and LEADER
#define K_TMUX TD(TD_TMUX)

// AltGr / Compose
//#define K_SYMBS TD(TD_ALTGR)
#define K_SYMBS LT(SYMBOLS,KC_SPC)
#ifdef AZERTY_LAYER_ENABLE
#define FR_SYMBS OSL(FR_ALTGR)
#endif

#define K_SPC KC_SPC

#define K_GNOME KC_F17 // to bind to window operations in Desktop

// Tap dances

#define CAPS_EXT TD(TD_CAPS)
#define K_CAPS TD(TD_CAPS)
#define K_CBR TD(TD_CBR)

// LEADER is a tap dance with Backslash
//#define K_LEAD TD(TD_LEAD)
#define K_LEAD TD(TD_BSLS)

// Boot on double tap
#define K_BOOT TD(TD_BOOT)

// Clear EEPROM on triple tap
#define K_EECLR TD(TD_EECLR)

// long press keys
#define LP_COLN LT(0,KC_COLN)   // tap: ':', long: '::'
#define LP_SLSH LT(0,KC_SLSH)   // tap: '/', long: '~/'
#define LP_SLSL LT(1,KC_SLSH)   // tap: '/', long: '// '  - symbols layer
#define LPS_PIPE LT(1,KC_PIPE)  // tap: '|',  shift '?', long: '||', shift long ' || '
#define LP_PIPE LT(0,KC_PIPE)   // tap: '|', long: ' || '
#define LPS_EQL LT(1,KC_EQL)    // tap: '=', long: '==', shift adds surrounding spaces
#define LP_EQL  LT(0,KC_EQL)    // tap: '=', long: ' = '
#define LP_EQEQ LT(0,KC_PEQL)   // tap: '==', long: ' == '
#define LPS_AMP LT(1,KC_AMPR)   // tap: '&', shift '^', long: '&&', shift adds surrounding spaces
#define LP_AMPR LT(0,KC_AMPR)   // tap: '&', long: ' && '
#define LP_EXLM LT(0,KC_EXLM)   // tap: '!', long: ' !! '
#define LP_LPRN LT(0,KC_LPRN)   // tap: '(', long: '()'
#define LP_LBRC LT(0,KC_LBRC)   // tap: '[', long: '[]'
#define LP_LCBR LT(1,KC_LCBR)   // tap: '{', long: '{}' - same keys as LBRC so change the layer
#define LP_RPRN LT(0,KC_RPRN)   // tap: ')', long: ');↵'
#define LP_COMM LT(0,KC_COMM)   // tap: ',', long: '', shift: '`', shift long: '```'
#define LP_DOT  LT(0,KC_DOT)    // tap: '.', long: '. ' one-shot shift, shift: '~', shift long: '~/workspace/'
#define LP_ASTCN LT(1,KC_ASTR)  // tap: '*', shift: ':', long shift: '::'
#define LPS_LT LT(1,KC_LT)      // tap: '<',  shift '"', long: '<=', shift long '""'
#define LPS_GT LT(1,KC_GT)      // tap: '>',  shift ''', long: '>=', shift long ''''
#ifdef AZERTY_LAYER_ENABLE
#define FL_SLSL LT(2,FR_SLSH)   // tap: '/', long: '// '  - symbols layer
#define FL_ASTCN LT(2,FR_ASTR)  // tap: '*', shift: ':', long shift: '::'
#define FL_COMM LT(1,FR_COMM)   // tap: ',', long: '', shift: '`', shift long: '```'
#define FL_DOT  LT(2,FR_DOT)    // tap: '.', long: '. ' one-shot shift, shift: '~', shift long: '~/workspace/'
#endif

// space / Tmux
#define LP_SPC LT(0,KC_SPC)   // tap: ' ', long: tmux

enum my_keycodes {
  CC_DISP = SAFE_RANGE,
  C_CLMK,               // Colemak layout (with HRM toggle)
  C_QWERT,              // Qwerty layout
  C_AZERT,              // Azerty adaptation layout
  C_1HAND,              // Mirrored one handed layout
  C_LLOCK,              // Lock the current layer
  C_OSLLCK,             // Lock the current one-shot layer
  C_NUMLK,              // Lock Numbers layer
  C_MEDIA,              // Media layer toggle
  C_MEDIA_MO,           // Media layer momentary
  CC_EMTG,              // Encode mode toggle
  CC_ECCW,              // Encoder counter clock wise
  CC_ECW,               // Encoder clock wise
  C_INDVAI,             // Indicators brightness +
  C_INDVAD,             // Indicators brightness -
  CC_LINE,              // Select whole line
  CC_DOTSC,             // Dot-Space-Caps
  CC_SRCN,              // Search: next result
  CC_SRCP,              // Search: previous result
  CC_RGBTG,             // RGB mostly off, used for indicators, toggle
  CC_RGBRT,             // RGB reset (not eeprom)
  CC_ANYK,              // For the extra B
  C_OSWIN,              // One shot LWIN  (Super)
  C_ALTTAB,             // Alt-tab in NAV layer
  C_PLSPLS,             // Symbol key for ++
  C_VIMCMD,             // vim: ESC colon
  C_SELECT,             // Select mode
  C_TMUX,               // Tmux mode (Ctrl-A before each key)  
  C_HELP,               // Display layer layout
  C_SYST,               // Enable the System layer
  C_UNDO,               // Language-aware undo (Ctrl-Z)
  C_QU,                 // Qu
  C_UNDS,               // Language-aware underscore
  C_MINS,               // Language-aware dash
  C_QUOT,               // Language-aware quote
  C_DQUO,               // Language-aware double quote
  C_COLN,               // Language-aware colon
  C_SCLN,               // Language-aware semi-colon
  C_EXLM,               // Language-aware exclamation mark
  C_PERC,               // Language-aware percent
  C_BSLS,               // Language-aware backslash
  CC_TEST
};
