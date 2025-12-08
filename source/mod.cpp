#include <mod.h>
#include <patch.h>
#include <cs/marioPouch.h>

namespace mod {

void mod_main()
{
   // Turn off the function thats used in all EVT scripts to set your coin count
   writeWord(cs::mario_pouch::SetCoin, 0x0, BLR);
   return;
}

}