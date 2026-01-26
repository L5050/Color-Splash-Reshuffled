// DO NOT CHANGE THIS FILE UNLESS YOU KNOW WHAT YOU'RE DOING

#include <mod.h>

#include <coreinit/dynload.h>
#include <whb/log.h>
#include <whb/log_console.h>
#include <whb/proc.h>

extern "C"
{
int rpl_init_mod(KernelCopyDataFn_t func)
{
  mod::_init_mod(func);
  return 0;
}

void exit(int turtle)
{
  turtle =1;
}
}


int rpl_entry(OSDynLoad_Module module, OSDynLoad_EntryReason reason)
{
  return 0; 
}