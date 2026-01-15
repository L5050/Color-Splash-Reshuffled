#pragma once

#include <common.h>


CPP_WRAPPER(wiiu::memory)

void * memcpy(void * dest, const void * src, s32 num);
void * memset(void * ptr, int value, s32 num);

inline void* MEMAlloc(size_t size) {
    return ((void*(*)(size_t))0x02413dac)(size);
}

inline void* MEMAllocEX(size_t size) {
    return ((void*(*)(size_t))0x02413df0)(size);
}

CPP_WRAPPER_END()

