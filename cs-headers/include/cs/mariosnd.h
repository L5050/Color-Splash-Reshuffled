#pragma once

#include <common.h>


CPP_WRAPPER(cs::mariosnd)

inline void playSnd(const char * param_1, const char * name, s32 param_3, s32 param_4) {
    return ((void(*)(const char * param_1, const char * name, s32 param_3, s32 param_4))0x025a1b34)(param_1, name, param_3, param_4);
}

CPP_WRAPPER_END()
