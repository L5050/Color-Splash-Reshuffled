#include <coreinit/dynload.h>
#include <common.h>

#ifndef MY_FIRST_RPL_H
#define MY_FIRST_RPL_H
typedef void (*KernelCopyDataFn_t)(u32 dst, u32 src, u32 len);

namespace mod {

void _init_mod(KernelCopyDataFn_t func);
void mod_main();

}

#endif // MY_FIRST_RPL_H
