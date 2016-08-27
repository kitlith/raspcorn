#pragma once

#ifndef RASPCORN_PERIPHERAL
#define RASPCORN_PERIPHERAL

#include <unicorn/unicorn.h>

#define PERIPHERAL_BASE 0x20000000 // TODO: Program Argument?

int peripheral_init(uc_engine *emu);

#endif /* end of include guard: RASPCORN_PERIPHERAL */
