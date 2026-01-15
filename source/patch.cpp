#include <mod.h>
#include <coreinit/memory.h>
#include <coreinit/cache.h>
#include <patch.h>
#include <common.h>
#include <cstdint>

namespace mod {

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
      *p = value;

      clear_DC_IC_Cache(ptr, sizeof(u32));

      return;
  }

  void _writeWord(void * ptr, u32 value)
  {
      int * p = (int *)(ptr);
      *p = value;
      clear_DC_IC_Cache(ptr, sizeof(u32));
      return;
  }

}