#pragma once

#include <common.h>


CPP_WRAPPER(cs::elfmgr)

void getElfData(Unk * param_1, char * name, Unk * param_3);
void loadElf(Unk * param_1, char * path);

CPP_WRAPPER_END()