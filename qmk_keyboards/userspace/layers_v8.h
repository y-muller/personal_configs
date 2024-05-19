
#ifndef _LAYERS_H_
#define _LAYERS_H_

enum layers{
#ifdef AZERTY_LAYER_ENABLE
    AZERTY,
#endif
    COLEMAK,
    COLEMAKH,
    NUMPAD,
    EXTEND,
    NAV,
    SYMBOLS,
    MACRO,
    SYSTEM,
#ifdef AZERTY_LAYER_ENABLE
    AZ_SYM,
#endif
};

#endif