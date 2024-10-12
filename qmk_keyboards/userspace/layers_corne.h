
#pragma once

enum layers{
    COLEMAKH, // with Home Row Mods
    COLEMAK,
#ifdef SWAP_HANDS_ENABLE
    ONEHAND,
#endif
#ifdef AZERTY_LAYER_ENABLE
    AZERTY,
#endif
    MEDIA,
    SYMBOLS,
#ifdef AZERTY_LAYER_ENABLE
    FR_SYMB,
    FR_ALTGR,
#endif
    EXTEND,
    NAV,
#ifdef SWAP_HANDS_ENABLE
    OH_SYMB,
#endif
    SYSTEM,
    LMODS,
    RMODS,
    LRMODS,
};
