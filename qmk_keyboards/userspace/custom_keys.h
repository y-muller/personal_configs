
#ifndef _CUSTOM_KEYS_H_
#define _CUSTOM_KEYS_H_



// KC_CAPS becomes Esc/Ctrl
#define ESC_CTL LCTL_T(KC_ESC)
//#define ESC_CTL KC_NO     // disabled while I get used to the layout
// or EXTEND
//#define L_EXTEND LT(0, KC_NO)
#define L_EXTEND OSL(EXTEND)
#define L_NAV OSL(NAV)
//#define L_EXTEND MO(EXTEND)
//#define L_NAV MO(NAV)
#ifdef ORTHO_FEATURES
#define L_NUM OSL(NUMBERS)
#else
#define L_NUM OSL(NUMPAD)
#endif
#define L_AZSYM OSL(AZ_SYM)

// KC_RALT becomes Compose/RAlt with Compose set to RWin in Gnome
//#define CMP_RALT RALT_T(KC_RWIN)
#define CMP_RALT RWIN_T(KC_RALT)
//#define CMP_RALT KC_RALT

// Rigth Shift is LEAD on tap
#define RS_LEAD TD(TD_RSFT_LEAD)

// Backslash is MACRO layer on hold
#define BSLS_MC LT(MACRO, KC_BSLS)

// Tab is MOUSE layer on hold
#ifdef ORTHO_FEATURES
#define TAB_MS LT(MOUSE, KC_TAB)
#endif

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
#define HRM_A LGUI_T(KC_A)
#define HRM_R LALT_T(KC_R)
#define HRM_S LSFT_T(KC_S)
#define HRM_T LCTL_T(KC_T)
#define HRM_N LCTL_T(KC_N)
#define HRM_E LSFT_T(KC_E)
#define HRM_I LALT_T(KC_I)
#define HRM_O LGUI_T(KC_O)

// Layout change keys
#define DF_CLMK  DF(COLEMAK)
#define DF_CLMKH DF(COLEMAKH)
#define DF_QWERT DF(QWERTY)
#define TG_CURSR TG(CURSOR)

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
//#define K_ALTGR TD(TD_ALTGR)
#define K_ALTGR LT(SYMBOLS,KC_SPC)

#define K_CAPS TD(TD_CAPS)

#define K_SPC KC_SPC

// LEADER is a tap dance with Backslash
//#define K_LEAD TD(TD_LEAD)
#define K_LEAD TD(TD_BSLS)

// Boot on double tap
#define K_BOOT TD(TD_BOOT)

// Clear EEPROM on triple tap
#define K_EECLR TD(TD_EECLR)

// long press keys
#define LP_COLN LT(0,KC_COLN) // tap: ':', long: '::'
#define LP_SLSH LT(0,KC_SLSH) // tap: '/', long: '~/'
#define LP_SLSL LT(1,KC_SLSH) // tap: '/', long: '// '  - symbols layer
#define LP_PIPE LT(0,KC_PIPE) // tap: '|', long: ' || '
#define LP_EQL  LT(0,KC_EQL)  // tap: '=', long: ' = '
#define LP_EQEQ LT(0,KC_PEQL) // tap: '==', long: ' == '
#define LP_AMPR LT(0,KC_AMPR) // tap: '&', long: ' && '
#define LP_EXLM LT(0,KC_EXLM) // tap: '!', long: ' !! '
#define LP_LPRN LT(0,KC_LPRN) // tap: '(', long: '()'
#define LP_LBRC LT(0,KC_LBRC) // tap: '[', long: '[]'
#define LP_LCBR LT(1,KC_LCBR) // tap: '{', long: '{}' - same keys as LBRC so change the layer
#define LP_RPRN LT(0,KC_RPRN) // tap: ')', long: ');↵'
#define LP_DOT  LT(0,KC_DOT)  // tap: '.', long: '. ' one-shot shift

enum my_keycodes {
  CC_DISP = SAFE_RANGE,
  C_CLMK1,              // Colemak layout 1
  C_CLMK2,              // Colemak layout 2 with Home Row Mods
  C_OSLLCK,             // Lock the current layer
  C_NUMLK,              // Lock Numbers layer
  C_MSTG,               // Mouse layer toggle
  CC_EMTG,              // Encode mode toggle
  CC_ECCW,              // Encoder counter clock wise
  CC_ECW,               // Encoder clock wise
  CC_LINE,              // Select whole line
  CC_DOTSC,             // Dot-Space-Caps
  CC_SRCN,              // Search: next result
  CC_SRCP,              // Search: previous result
  CC_RGBTG,             // RGB mostly off, used for indicators, toggle
  CC_RGBRT,             // RGB reset (not eeprom)
  CC_ANYK,              // For the extra B
  C_PLSPLS,             // Symbol key for ++
  CC_HELP,
  CC_TEST
};

#endif
