#include <coreinit/dynload.h>

#ifndef MY_FIRST_RPL_H
#define MY_FIRST_RPL_H

namespace mod {

void mod_main();

}

int
my_first_export();

int
rpl_entry(OSDynLoad_Module module,
          OSDynLoad_EntryReason reason);

#endif // MY_FIRST_RPL_H
