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

extern "C"
{
  f32 _speedBuff = 0.85f;
  void * speedRet = (void *)0x0220b07c;
  void * levelUpRet = (void *)0x02211b08;
  void * XPRet = (void *)0x02211050;
  void * _damageFunc = (void *)0x0213c1e8; 
  void * _isEnemyBuffFixRet = (void *)0x0213dcf4;
  void * _kamekRet = (void *)0x0218b138;
  f32 _healthBuff = 0.3f;
  int _isNpcMario = 0;
  f32 _fixSoftlock = 1.0f;
  f32 _fixBigDamage = 199.0f;

  void _handleKamek();
    asm
    (
      ".global _handleKamek\n"
      "_handleKamek:\n"
      "li 0, 0x2\n"
      "stw 0, 0x1d10(31)\n"
      "lis 5, _kamekRet@ha\n"
      "lwz 5, _kamekRet@l(5)\n"
      "mtctr 5\n"
      "bctr\n"
    );

  void _patchMarioSpeed();
    asm
    (
      ".global _patchMarioSpeed\n"
      "_patchMarioSpeed:\n"
      "lis 5, _speedBuff@ha\n"
      "lfs 2, _speedBuff@l(5)\n"
      "lis 5, speedRet@ha\n"
      "lwz 5, speedRet@l(5)\n"
      "mtctr 5\n"
      "bctr\n"
    );

  void _patchLevelUps();
  asm(
    ".global _patchLevelUps\n"
    "_patchLevelUps:\n"
    "add 0, 12, 3\n"
    "li 3, 0x1E\n"
    "add 0, 0, 3\n"
    "lis 5, levelUpRet@ha\n"
    "lwz 5, levelUpRet@l(5)\n"
    "mtctr 5\n"
    "bctr\n"
    );

  void _patchXp();
  asm(
    ".global _patchXp\n"
    "_patchXp:\n"
    "add. 12, 11, 4\n"
    "add. 12, 11, 4\n"
    "lis 5, XPRet@ha\n"
    "lwz 5, XPRet@l(5)\n"
    "mtctr 5\n"
    "bctr\n"
    );
    
  void _makeMartyoDamageVisible();
  asm(
    ".global _makeMartyoDamageVisible\n"
    "_makeMartyoDamageVisible:\n"
    "li 8, 0\n"
    "cmpwi 8, 0\n"
    "blr\n"
    );
    
  void _visibleDamageCheck();
  asm(
    ".global _visibleDamageCheck\n"
    "_visibleDamageCheck:\n"
    "cmpwi 8, 2\n"
    "beq _makeMartyoDamageVisible\n"
    "cmpwi 8, 0\n"
    "blr\n"
    );
    
  void _isEnemyBuffFix();
  asm(
    ".global _isEnemyBuffFix\n"
    "_isEnemyBuffFix:\n"
    "lis 4, _isNpcMario@ha\n"
    "ori 4, 4, _isNpcMario@l\n"
    "li 3, 0\n"
    "stw 3, 0(4)\n"
    "lis 5, _isEnemyBuffFixRet@ha\n"
    "lwz 5, _isEnemyBuffFixRet@l(5)\n"
    "mtctr 5\n"
    "bctr\n"
    );
    
  void _fixDamageBuffIssue();
  asm(
    ".global _fixDamageBuffIssue\n"
    "_fixDamageBuffIssue:\n"
    "lis 4, _damageFunc@ha\n"
    "lwz 4, _damageFunc@l(4)\n"
    "cmpw 0, 4, 5\n"
    "bne _isEnemyBuffFix\n"
    "lis 4, _isNpcMario@ha\n"
    "ori 4, 4, _isNpcMario@l\n"
    "li 3, 1\n"
    "stw 3, 0(4)\n"
    "lis 5, _isEnemyBuffFixRet@ha\n"
    "lwz 5, _isEnemyBuffFixRet@l(5)\n"
    "mtctr 5\n"
    "bctr\n"
    );

  void _moreDamage();
  asm(
    ".global _moreDamage\n"
    "_moreDamage:\n"
    "lis 4, _isNpcMario@ha\n"
    "lwz 4, _isNpcMario@l(4)\n"
    "cmpwi 4, 1\n"
    "bne _isEnemy\n"
    "li 4, 0\n"
    "lis 5, _healthBuff@ha\n"
    "lfs 3, _healthBuff@l(5)\n"
    "fmuls 10, 10, 3\n"
    "fsubs 29, 29, 10\n"
    "li 5, 0\n"
    "blr\n"
    );
    
  void _maxHpDefense();
  asm(
    ".global _maxHpDefense\n"
    "_maxHpDefense:\n"
    "fmr 10, 4\n"
    "fsubs 29, 29, 10\n"
    "blr\n"
    );
    
  void _isEnemy();
  asm(
    ".global _isEnemy\n"
    "_isEnemy:\n"
    "li 4, 0x0\n"
    "li 5, 0x0\n"
    "fadd 10, 10, 10\n"
    "lis 5, _fixSoftlock@ha\n"
    "lfs 3, _fixSoftlock@l(5)\n"
    "lis 5, _fixBigDamage@ha\n"
    "lfs 4, _fixBigDamage@l(5)\n"
    "fcmpo 0, 10, 4\n"
    "bgt _maxHpDefense\n"
    "fsubs 10, 10, 3\n"
    "fsubs 29, 29, 10\n"
    "blr\n"
    );
}


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
    //cs::mario_pouch::SetCoin(0); relocation testing only
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

int makeBlackPaint()
{
  ((void (*)())0x0248c620)();
  return 1;
}

int* makeBlackPaint2(s32 *unithandle)
{
  ((void (*)(int * handle, int parts, f32 r, f32 g, f32 b, f32 a))0x024e2a0c)(unithandle, 0, 0.0f, 0.0f, 0.0f, 155.0f);
  return unithandle;
}

int* makeBlackPaint3(s32 *unithandle)
{ 
  ((void (*)(int integer))0x0254614c)(0x1);
  ((void (*)(int integer))0x02546118)(0x1);
  return ((int* (*)(int* pointer))0x0226dbcc)(unithandle);
}

void fixCutOut(int* pointer)
{ 
  asm("mr 3, 30");
  return ((void (*)(int* integer, int cutout))0x02306a68)(pointer, 0x5);
}

f32 fixCutoutFloat()
{
  return 75.0f;
}

void patchPaintedItems(cs::mario_pouch::MarioPouch* pouchPanels, s32 id)
{
  if (id > 0xf3 && id < 0x12b)
  {
    id += -0x94;
  }
  OSReport("card id %d", id);
  return cs::mario_pouch::AddPanelByID(pouchPanels, id);
}

void mod_main()
{
   // Turn off the function thats used in all EVT scripts to set your coin count
   writeWord(cs::mario_pouch::SetCoin, 0x0, BLR);
   // Speed up btl spin menu slightly
   writeWord(cs::btl_spin::btlSpinMain, 0x0, 0x3800000A);
  writeBranch(0x02567cec, 0x0, makeBlackPaint);
   
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

  //writeBranch(0x024b25c0, 0x0, makeBlackPaint2);
  writeBranchLink(0x02567c3c, 0x0, makeBlackPaint3);

  //writeBranchLink(0x02305e5c, 0x0, fixCutOut);

  // assembly patch BLRs and NOPs
   writeWord(0x0218fe1c, 0x0, BLR);
   writeWord(0x0218d578, 0x0, BLR);
   writeWord(0x02475650, 0x0, BLR);
   writeWord(0x0218801c, 0x0, NOP);
   writeWord(0x02312ad8, 0x0, NOP);
   writeWord(0x02312adc, 0x0, NOP);
   writeWord(0x02312ae8, 0x0, NOP); 
   writeWord(0x02312adc, 0x0, NOP);
   //writeWord(0x0220b080, 0x0, NOP);

   // assembly patch for cutout floats
  writeBranchLink(0x02312b34, 0x0, fixCutoutFloat);
  writeBranchLink(0x02312b40, 0x0, fixCutoutFloat);
  writeBranch(0x02312dfc, 0x0, fixCutOut); 
  writeBranch(0x0220b078, 0x0, _patchMarioSpeed);

  // level up assembly patch
  writeBranch(0x02211b04, 0x0, _patchLevelUps);
  writeBranch(0x0221104c, 0x0, _patchXp);

  // painted items patch
  writeBranch(0x0221249c, 0x0, patchPaintedItems);

  // damage numbers patch
  writeBranchLink(0x02140cb4, 0x0, _visibleDamageCheck);

  // health change patch
  writeBranchLink(0x0213dd14, 0x0, _moreDamage);
  writeBranchLink(0x0213dcf0, 0x0, _fixDamageBuffIssue);

  // fix kamek 
  writeBranchLink(0x0218fbf8, 0x0, _handleKamek);

  return;
}

}