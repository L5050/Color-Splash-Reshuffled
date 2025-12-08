#pragma once

#include <common.h>


CPP_WRAPPER(cs::mario_pouch)

typedef struct {
  s32 red;
  s32 yellow;
  s32 blue;
} GameInk;

s32 GetCoin();
void SetCoin(s32 count);
void AddCoin(s32 count);
void AddKeyItem(const char *key);
s32 GetMaxHP();
s32 GetHP();
void SetHP(s32 hp);
void GetInk(GameInk * ink);

CPP_WRAPPER_END()