#pragma once

#include <common.h>


CPP_WRAPPER(cs::evt)

inline bool isGF(const char * name) {
    return ((bool(*)(const char * name))0x02482968)(name);
}
inline void onGF(const char * name) {
    return ((void(*)(const char * name))0x024829bc)(name);
}

inline void offGF(const char * name) {
    return ((void(*)(const char * name))0x02482a1c)(name);
}

CPP_WRAPPER_END()
