#pragma once

#include <common.h>


CPP_WRAPPER(cs::btl_unit)

inline int * GetUnitHandle(Unk * idk, s32 id) {
    return ((int *(*)(Unk * idk, s32 id))0x024affd8)(idk, id);
}

inline bool IsPlayer(int * Unithandle) {
    return ((bool(*)(int * Unithandle))0x024c8044)(Unithandle);
}

CPP_WRAPPER_END()
