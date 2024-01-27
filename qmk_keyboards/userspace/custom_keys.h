

#ifndef _CUSTOM_KEYS_H_
#define _CUSTOM_KEYS_H_

enum my_keycodes {
  CC_DISP = SAFE_RANGE + 10, // QK_USER? // Thinkpad display switching F7
  CC_ELOCK,             // Lock Extend layer
  CC_RGBTG,             // RGB mostly off, used for indicators, toggle
  CC_RGBRT,             // RGB reset (not eeprom)
  CC_ANYK,              // For the extra B
  CC_TEST
};

#endif