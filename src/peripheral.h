#pragma once

#ifndef RASPCORN_PERIPHERAL
#define RASPCORN_PERIPHERAL

#include <unicorn/unicorn.h>

int peripheral_init(uc_engine *emu, uint64_t peripheral_base);

#endif /* end of include guard: RASPCORN_PERIPHERAL */
