#pragma once

#ifndef RASPCORN_PERIPH_GPIO
#define RASPCORN_PERIPH_GPIO

#include "../peripheral.h"

#define GPIO_BASE (PERIPHERAL_BASE + 0x00200000)
#define GPFSEL1 0x04
#define GPSET0  0x1C
#define GPCLR0  0x28

int gpio_init(uc_engine *emu);

#endif /* end of include guard: RASPCORN_PERIPH_GPIO */
