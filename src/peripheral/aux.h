#pragma once

#ifndef RASPCORN_PERIPH_AUX
#define RASPCORN_PERIPH_AUX

#include "../peripheral.h"

#define AUX_BASE (PERIPHERAL_BASE + 0x00215000)

int aux_init(uc_engine *emu);

#endif /* end of include guard: RASPCORN_PERIPH_AUX */
