#include <mod.h>
#include <coreinit/debug.h>
#include <patch.h>
#include <cs/btl_spin.h>
#include <cs/marioPouch.h>
#include <cs/rand.h>
#include <cs/mariosnd.h>
#include <cs/btl_ac.h>
#include <cs/btl_unit.h>
#include <cs/evt.h>
#include <cs/btl_eff.h>
#include <cstring>

namespace mod {

char battleSpinNameBuffer[10];
int * btlspin_backup = nullptr;
char battleSpinBuffer[70];
int lemmyCount = 0;
u32 modVpadFlags = 0;
int hopefullyThisWorks = 0;
int turtle10backup = 0;

char *removeSubstring(char *mainString, const char *subString)
{
  size_t subLen = strlen(subString);
  if (subLen == 0)
  {
    return mainString;
  }

  char *p = mainString;
  while ((p = strstr(p, subString)) != NULL)
  {
    memmove(p, p + subLen, strlen(p + subLen) + 1);
  }
  return mainString;
}

char *custom_strstr_because_ppc_sucks(const char *haystack, const char *needle)
{
  if (*needle == '\0')
  {
    return (char *)haystack;
  }

  while (*haystack != '\0')
  {
    const char *h_ptr = haystack;
    const char *n_ptr = needle;

    while (*n_ptr != '\0' && *h_ptr != '\0' && *h_ptr == *n_ptr)
    {
      h_ptr++;
      n_ptr++;
    }

    if (*n_ptr == '\0')
    {
      return (char *)haystack;
    }

    haystack++;
  }

  return NULL;
}

const char *new_GetBattleSpinCard(Unk *param_1, const char *param_2, s32 param_3)
{
  const char *ret = cs::btl_spin::GetBattleSpinCard(param_1, param_2, param_3);
  if (strcmp(ret, "PNL_1UP_KINOKO_100") == 0)
  {
    return "PNL_KINOKO_100";
  }
  else
  {
    return ret;
  }
}

const char *new_GetBattleSpinCard2(Unk *param_1, const char *param_2, s32 param_3)
{
  battleSpinNameBuffer[3] = '\0';
  if (strcmp((const char *)battleSpinNameBuffer, "MTN") == 0)
  {
    return "PNL_EXTINGUISHER";
  }
  if (strcmp((const char *)battleSpinNameBuffer, "IGY") == 0)
  {
    return "PNL_BONE";
  }
  if (strcmp((const char *)battleSpinNameBuffer, "LDW") == 0)
  {
    return "PNL_BALLOON";
  }
  if (strcmp((const char *)battleSpinNameBuffer, "WDY") == 0)
  {
    return "PNL_INSTANT_CAMERA";
  }
  if (strcmp((const char *)battleSpinNameBuffer, "LAR") == 0)
  {
    return "PNL_CORK";
  }
  if (strcmp((const char *)battleSpinNameBuffer, "LMY") == 0)
  {
    return "PNL_ICE_PICK";
  }
  if (strcmp((const char *)battleSpinNameBuffer, "ROY") == 0)
  {
    return "PNL_WASHER";
  }
  return cs::btl_spin::GetBattleSpinCard(param_1, param_2, param_3);
}

int *BtlSpinNameHook(int *param_1, s32 param_2)
{
  int *ret = ((int *(*)(int *param_1, s32 param_2))0x0212ead8)((int *)0x4f9c2c88, param_2);
  if (ret == nullptr)
  {
    return nullptr;
  }
  ret = (int*)((char*)ret + 0x2d44);
  if ((int)ret > 0x02000000)
  {

    const char * turtle = (const char *)*ret;
    if (strcmp((const char *)turtle, "MTN") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
    if (strcmp((const char *)turtle, "IGY") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
    if (strcmp((const char *)turtle, "LDW") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
    if (strcmp((const char *)turtle, "WDY") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
    if (strcmp((const char *)turtle, "LAR") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
    if (strcmp((const char *)turtle, "LMY") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
    if (strcmp((const char *)turtle, "ROY") == 0)
    {
      strcpy(battleSpinNameBuffer, (const char *)turtle);
    }
  }
  return ((int *(*)(int *param_1, s32 param_2))0x0212ead8)((int *)0x4f9c2c88, param_2);
}

s32 randomCrits(s32 curLvl)
{
  s32 chance = cs::rand::irand(0);
  if (chance == 0)
  {
    return 7; // 7 is an excellent
  }
  if (curLvl > 6)
  {
    curLvl = 6;
  }
  return curLvl;
}

s32 patchVpad(s32 isLoaded, u32 vpadFlags)
{
  modVpadFlags = vpadFlags;
  u32 result = modVpadFlags & 0x4000;
  if (result != 0)
  {
    if ((s32)cs::mario_pouch::GetPanelNum < 99)
    {
      //cs::mario_pouch::AddPanel("PNL_BOM");
    }
  }
  result = vpadFlags & 0x8000;
  if (result != 0)
  {
    asm("li 10, 0x100");
  }
  return 1;
}

u32 newMsgIsBusy(u32 IsBusy, u32 unk)
{
  u32 result = modVpadFlags & 0x4000;
  if (result != 0)
  {
    return 1;
  }
  return 0;
}

void colorEnemy(s32 one, s32 two, s32 three)
{
  asm("li 3, 0");
  asm("li 4, 0");
  int * pointer = cs::btl_unit::GetUnitHandle((Unk *)one, two);
  //bool isPlayer = cs::btl_unit::IsPlayer(pointer);
  //asm("li 4, 0x1");
  bool goodCondition = true; //cs::btl_eff::IsValidCondition(pointer, two);
  if (goodCondition){ 
  cs::btl_eff::SetCondition(pointer, 0xd, 13);
  cs::btl_eff::SetCondition(pointer, 0xe, 13);
  }
  return;
}

int patchRedRescue(int turtle)
{
  bool gf = true;//cs::evt::isGF("GF_EXT_GB_Finished_RedRescue");
  if (gf)
  {
    //cs::evt::onGF("GF_EXT_GB_Finished_RedRescue");
  }
  return turtle;
}

void marioDamageBuff4(int turtle3, int turtle4, int turtle5, int turtle6, int turtle7, int turtle8, int turtle9)
{
  hopefullyThisWorks = turtle9;
  return;
}

void marioDamageBuff3(int turtle3, int turtle4, int turtle5, int turtle6, int turtle7, int turtle8, int turtle9)
{
  asm("lwz 9, 0x126c(28)");
  if (turtle9 == turtle10backup)
  {
    turtle9 = hopefullyThisWorks;
    marioDamageBuff4(turtle3, turtle4, turtle5, turtle6, turtle7, turtle8, turtle9);
    asm("stw 9, 0x126c(28)");
  }
  return;
}

void marioDamageBuff2(int turtle3, int turtle4, int turtle5, int turtle6, int turtle7, int turtle8, int turtle9, int turtle10, float fTurtle1, float fTurtle2)
{
  hopefullyThisWorks = turtle10;
  return;
}

bool marioDamageCheck(int* param_1, int *param_2)
{
  if (param_1 == param_2)
  {
    return 1;
  }
  return 0;
}

void marioDamageBuff(int turtle3, int turtle4, int* turtle5, int turtle6, int turtle7, int turtle8, int turtle9, int turtle10, float fTurtle1, float fTurtle2)
{
  int currentLevel = (*cs::mario_pouch::GetMarioPouch())->xpStruct.level;
  // f32 damage = (f32)turtle10;
  turtle10backup = turtle10;
  f32 fCurrentLevel = (f32)currentLevel;
  f32 damageBuff = (fCurrentLevel / 10.0f) + 1.0f;
  OSReport("turtledamagebuff %f", damageBuff);
  turtle10 = turtle10 * damageBuff;
  OSReport("turtle10 %d", turtle10);
  asm("mr 10, 4");
  asm("stw 10, 0x126c(27)");
  marioDamageBuff2(turtle3, turtle4, *turtle5, turtle6, turtle7, turtle8, turtle9, turtle10, fTurtle1, fTurtle2);
  asm("lis 9, 0x1002");
  asm("xoris 7, 10, 0x8000");
  return;
}

void mod_main()
{
   // Turn off the function thats used in all EVT scripts to set your coin count
   writeWord(cs::mario_pouch::SetCoin, 0x0, BLR);
   // Speed up btl spin menu slightly
   writeWord(cs::btl_spin::btlSpinMain, 0x0, 0x3800000A);
   
   writeBranchLink(0x021a2018, 0x0, new_GetBattleSpinCard);
   
   writeBranchLink(0x021a22e4, 0x0, new_GetBattleSpinCard);

   writeBranchLink(0x021a2480, 0x0, new_GetBattleSpinCard2);

   //writeBranchNE(0x021a1ef8, 0x0, BtlSpinPatch);

   writeBranchLink(0x021a1e94, 0x0, BtlSpinNameHook);

   writeBranchLink(0x0243b6f8, 0x0, patchVpad); 
   writeWord(0x0243b6fc, 0x0, NOP);
   writeWord(0x0243b700, 0x0, NOP);

   writeBranch(0x025e618c, 0x0, newMsgIsBusy);

   writeBranch(0x02493594, 0x14C, randomCrits);

   writeBranch(0x024c407c, 0x0, colorEnemy);

   writeBranchLink(0x0213dcf4, 0x0, marioDamageBuff);
   writeBranchLink(0x02141674, 0x0, marioDamageBuff3); 
   writeWord(0x024c9590, 0x0, BLR);
   writeWord(0x024c9468, 0x0, BLR);

   return;
}

}