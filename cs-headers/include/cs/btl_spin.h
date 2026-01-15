#pragma once

#include <common.h>


CPP_WRAPPER(cs::btl_spin)

inline void initBtlSpin(Unk * param_1) {
    return ((void (*)())0x021a1e08)();
}

inline void btlSpinMain(Unk * param_1) {
    return ((void (*)())0x021a2d5c)();
}

inline const char * GetBattleSpinCard(Unk * param_1, const char * param_2, s32 param_3) {
    return ((const char *(*)())0x021a1a40)();
}

CPP_WRAPPER_END()
