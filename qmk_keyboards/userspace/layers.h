
#ifndef _LAYERS_H_
#define _LAYERS_H_

enum layers{
#ifdef AZERTY_LAYER_ENABLE
    AZERTY,
#endif
    COLEMAK,
    EXTEND,
    NAV,
    NUMPAD,
    SYSTEM,
#ifdef AZERTY_LAYER_ENABLE
    AZ_SYM,
#endif
};

#endif