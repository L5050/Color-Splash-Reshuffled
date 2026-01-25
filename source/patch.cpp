#include <mod.h>
#include <coreinit/memory.h>
#include <coreinit/cache.h>
#include <coreinit/memorymap.h>
#include <patch.h>
#include <common.h>
#include <cstdint>

namespace mod {

KernelCopyDataFn_t KernelCopyDataFn;

void _init_mod(KernelCopyDataFn_t func)
{
  if (func == nullptr)
  {
    return;
  }
  KernelCopyDataFn = func;
  return mod::mod_main();
}

void clear_DC_IC_Cache(void * ptr, u32 size)
{
    DCFlushRange(ptr, size);
    ICInvalidateRange(ptr, size);
    return;
}

  void _writeBranch(void * ptr, void * destination, bool link)
  {
      u32 delta = reinterpret_cast<u32>(destination) - reinterpret_cast<u32>(ptr);
      u32 value = link ? 0x48000001 : 0x48000000;
      value |= (delta & 0x03FFFFFC);
      
      u32 * p = reinterpret_cast<u32 *>(ptr);
      KernelCopyDataFn(OSEffectiveToPhysical((u32)p), OSEffectiveToPhysical((u32)(u32*)ptr), sizeof(u32));
      //*p = value;

      clear_DC_IC_Cache(ptr, sizeof(u32));

      return;
  }

  void _writeWord(void * ptr, u32 value)
  {
      int * p = (int *)(ptr);
      //*p = value;
      KernelCopyDataFn(OSEffectiveToPhysical((u32)p), OSEffectiveToPhysical((u32)(u32*)ptr), sizeof(u32));
      clear_DC_IC_Cache(ptr, sizeof(u32));
      return;
  }

}