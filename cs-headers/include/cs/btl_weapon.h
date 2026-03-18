#pragma once

#include <common.h>


CPP_WRAPPER(cs::btl_weapon)

struct PaintCost {
    u8 red;
    u8 blue;
    u8 yellow;
};

struct BattleWeapon {
    char *name;
    struct PaintCost cost;
    u8 padding_0x7;
    int field3_0x8;
    int attack_count;
    int attack_wave_count;
    int field6_0x14;
    int field7_0x18;
    int field8_0x1c;
    int field9_0x20;
    int field10_0x24;
    int field11_0x28;
    int field12_0x2c;
    int field13_0x30;
    int field14_0x34;
    int field15_0x38;
    int Unpainted_Base_Damage;
    int Painted_Bonus_Damage;
    int field18_0x44;
    int Bonus_Damage_1;
    int Bonus_Damage_2;
    int Bonus_Damage_3;
    int Bonus_Damage_4;
    int Bonus_Damage_5;
    int Bonus_Damage_6;
    int Bonus_Damage_7;
    int Bonus_Damage_8;
    int Bonus_Damage_9;
    int field28_0x6c;
    int field29_0x70;
    int field30_0x74;
    int field31_0x78;
    int field32_0x7c;
    int field33_0x80;
    int field34_0x84;
    int field35_0x88;
    int field36_0x8c;
    int field37_0x90;
    int field38_0x94;
    int field39_0x98;
    short field40_0x9c;
    short field41_0x9e;
    short field42_0xa0;
    short field43_0xa2;
    int field44_0xa4;
    int field45_0xa8;
    int field46_0xac;
    int field47_0xb0;
    int field48_0xb4;
    int field49_0xb8;
    int field50_0xbc;
    int field51_0xc0;
    int field52_0xc4;
    int field53_0xc8;
    int field54_0xcc;
    int field55_0xd0;
    int field56_0xd4;
    int field57_0xd8;
    int field58_0xdc;
    int field59_0xe0;
    int field60_0xe4;
    int field61_0xe8;
    int field62_0xec;
    char *script_path;
    char *attack_type;
    char *field65_0xf8;
    char *thing_group;
    char *thing_path;
    char *field68_0x104;
    int field69_0x108;
    int field70_0x10c;
};

inline BattleWeapon * returnWeaponData(char *name) {
    return ((BattleWeapon *(*)(char *name))0x021ec5d4)(name);
}


CPP_WRAPPER_END()
