#pragma once

#ifndef RASPCORN_PERIPH_GPIO
#define RASPCORN_PERIPH_GPIO

#include "../peripheral.h"

#define GPIO_BASE 0x00200000
#define GPFSEL0 0x00
#define GPFSEL1 0x04

#define GPSET0  0x1C

#define GPCLR0  0x28

#define GPLEV0  0x34

#define GPEDS0  0x40

#define GPREN0  0x4C

#define GPFEN0  0x58

enum gpioFunction {
    GPIO_INPUT = 0b000,
    GPIO_OUTPUT = 0b001,
    GPIO_ALT0 = 0b100,
    GPIO_ALT1 = 0b101,
    GPIO_ALT2 = 0b110,
    GPIO_ALT3 = 0b111,
    GPIO_ALT4 = 0b011,
    GPIO_ALT5 = 0b010
};

struct gpioPin {
    enum gpioFunction function;
    bool status;
};

int gpio_init(uc_engine *emu, uint64_t peripheral_base);

#endif /* end of include guard: RASPCORN_PERIPH_GPIO */
