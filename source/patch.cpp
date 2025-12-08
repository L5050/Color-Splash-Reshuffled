#include <mod.h>
#include <patch.h>
#include <common.h>

namespace mod {

  void _writeBranch(void * ptr, void * destination, bool link)
  {
      u32 delta = reinterpret_cast<u32>(destination) - reinterpret_cast<u32>(ptr);
      u32 value = link ? 0x48000001 : 0x48000000;
      value |= (delta & 0x03FFFFFC);
      
      u32 * p = reinterpret_cast<u32 *>(ptr);
      *p = value;

      return;
  }

  void _writeWord(void * ptr, u32 value)
  {
      int * p = (int *)(ptr);
      *p = value;
  }

}