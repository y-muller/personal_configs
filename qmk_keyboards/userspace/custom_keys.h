

#ifndef _CUSTOM_KEYS_H_
#define _CUSTOM_KEYS_H_

enum my_keycodes {
  CC_DISP = SAFE_RANGE + 10, // QK_USER? // Thinkpad display switching F7
  CC_ELOCK,             // Lock Extend layer
  CC_EMTG,              // Encode mode toggle
  CC_ECCW,              // Encoder counter clock wise
  CC_ECW,               // Encoder clock wise
  CC_SRCN,              // Search: next result
  CC_SRCP,              // Search: previous result
  CC_RGBTG,             // RGB mostly off, used for indicators, toggle
  CC_RGBRT,             // RGB reset (not eeprom)
  CC_ANYK,              // For the extra B
  CC_HELP,
  CC_TEST
};

#endif