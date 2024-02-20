


// KC_CAPS becomes Esc/Ctrl
//#define ESC_CTL LCTL_T(KC_ESC)
#define ESC_CTL KC_NO     // disabled while I get used to the layout
// or EXTEND
//#define L_EXTEND LT(0, KC_NO)
#define L_EXTEND OSL(EXTEND)
#define L_NAV OSL(NAV)
#define L_AZSYM OSL(AZ_SYM)

// KC_RALT becomes Compose/RAlt with Compose set to RWin in Gnome
#define CMP_RALT RALT_T(KC_RWIN)

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

// Tabs left and right
#define K_TAB_L CA(KC_PGUP)
#define K_TAB_R CA(KC_PGDN)

// Delete Previous Word (Ctrl+Backspace)
#define KS_DPW LCTL(KC_BSPC)
// Alt+Home (real Home for CodeLite: start of line)
#define KS_AHOM A(KC_HOME)

// TMUX key is a tap dance with HELP and LEADER
#define K_TMUX TD(TD_TMUX)

// LEADER is a tap dance with Backslash
#define K_LEAD TD(TD_LEAD)

// Boot on double tap
#define K_BOOT TD(TD_BOOT)

#ifndef _CUSTOM_KEYS_H_
#define _CUSTOM_KEYS_H_

enum my_keycodes {
  CC_DISP = SAFE_RANGE + 10, // QK_USER? // Thinkpad display switching F7
  CC_ELOCK,             // Lock Extend layer
  CC_EMTG,              // Encode mode toggle
  CC_ECCW,              // Encoder counter clock wise
  CC_ECW,               // Encoder clock wise
  CC_LINE,              // Select whole line
  CC_SRCN,              // Search: next result
  CC_SRCP,              // Search: previous result
  CC_RGBTG,             // RGB mostly off, used for indicators, toggle
  CC_RGBRT,             // RGB reset (not eeprom)
  CC_ANYK,              // For the extra B
  CC_HELP,
  CC_TEST
};

#endif