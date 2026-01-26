// DO NOT CHANGE THIS FILE UNLESS YOU KNOW WHAT YOU'RE DOING

#include <mod.h>

#include <coreinit/dynload.h>


int rpl_entry(OSDynLoad_Module module, OSDynLoad_EntryReason reason)
{
   mod::mod_main();
   return 1;
}