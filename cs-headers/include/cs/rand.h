#pragma once

#include <common.h>


CPP_WRAPPER(cs::rand)

inline s32 irand(s32 max) {
    return ((s32(*)())0x02413cf0)();
}

CPP_WRAPPER_END()
