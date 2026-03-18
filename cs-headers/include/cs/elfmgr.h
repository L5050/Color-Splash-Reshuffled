#pragma once

#include <common.h>


CPP_WRAPPER(cs::elfmgr)


inline void getElfData(void * param_1, char * name, Unk * param_3){
    return ((void (*)(void * param_1, char * name, Unk * param_3))0x02339c60)(param_1, name, param_3);
}


void loadElf(Unk * param_1, char * path);

CPP_WRAPPER_END()