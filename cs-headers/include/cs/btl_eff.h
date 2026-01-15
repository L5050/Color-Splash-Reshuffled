#pragma once

#include <common.h>


CPP_WRAPPER(cs::btl_eff)

inline void SetCondition(s32 * UnitHandle, s32 condition, s32 turns) {
    return ((void(*)(s32 * UnitHandle, s32 condition, s32 turns))0x024c8f04)(UnitHandle, condition, turns);
}

inline bool IsValidCondition(int * Unithandle, int condition) {
    return ((bool(*)(int * Unithandle, int condition))0x024c8fbc)(Unithandle, condition);
}

CPP_WRAPPER_END()
