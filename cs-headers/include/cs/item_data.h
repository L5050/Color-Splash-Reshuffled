#pragma once

#include <common.h>


CPP_WRAPPER(cs::item_data)

struct ItemEntry {
    char * id;
    int ItemType;
    char * ItemData;
    char * Model_ID;
    char * Texture_ID;
    short Buy_Price;
    short Sell_Price;
    u8 Coin_Value;
    u8 field8_0x19;
    short Red_Paint_Value;
    short Yellow_Paint_Value;
    short Blue_Paint_Value;
    u8 HP_Value;
    u8 XP_Value;
    short field14_0x22;
    char * Name_String;
    char * field16_0x28;
    char * Help_String;
    char * field18_0x30;
    int field19_0x34;
    char * field20_0x38;
    int field21_0x3c;
    int field22_0x40;
    char * init_function;
    char * get_function;
    char * item_type;
    int field26_0x50;
    int field27_0x54;
};

struct ItemSet {
    char *ID;
    short itemCount;
    short itemEntryCount;
    char *itemEntry;
    char *itemEntry2;
    char *itemEntry3;
    int field6_0x14;
    short Item_1_Drop_Chance;
    short Item_2_Drop_Chance;
    short Item_3_Drop_Chance;
    short field10_0x1e;
    short field11_0x20;
    short field12_0x22;
};

inline ItemEntry*** GetItemData() {
    return (ItemEntry***)0x100b4e00;
}

inline ItemSet** GetItemSetData() {
    return (ItemSet**)0x100b4e10;
}

CPP_WRAPPER_END()
