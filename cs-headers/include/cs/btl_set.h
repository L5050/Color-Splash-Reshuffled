#pragma once

#include <common.h>


CPP_WRAPPER(cs::btl_set)

struct EnemyList {
    int field0_0x0;
    char * enemyID;
    int position;
    int field3_0xc;
    int field4_0x10;
    int field5_0x14;
    int field6_0x18;
    int field7_0x1c;
    int field8_0x20;
    int field9_0x24;
};

struct BattleEncounter {
    char *ID;
    char *Description;
    struct EnemyList *Enemy_List;
    char * Battle_Map;
    char * BGM;
    int field5_0x14;
    int field6_0x18;
    short field7_0x1c;
    short field8_0x1e;
    short field9_0x20;
    short field10_0x22;
    int field11_0x24;
    char * field12_0x28;
    char * Level_ID;
    char * Script_Function;
};

inline BattleEncounter * returnSetData(char *name) {
    return ((BattleEncounter *(*)(char *name))0x021ec508)(name);
}


CPP_WRAPPER_END()
