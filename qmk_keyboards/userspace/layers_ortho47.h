
#ifndef _LAYERS_ORTHO47_H_
#define _LAYERS_ORTHO47_H_

enum layers{
    COLEMAK,
    COLEMAKH, // with Home Row Mods
#ifdef AZERTY_LAYER_ENABLE
    FRENCH,   // when host is set to AZERTY
#endif
    CURSOR,
    MEDIA,
    EXTEND,
    NAV,
    SYMBOLS,
    NUMBERS,
#ifdef AZERTY_LAYER_ENABLE
    FR_SYMS,
    FR_CHARS,
    FR_NUMS,
#endif
    MACRO,
    SYSTEM,
};

#endif