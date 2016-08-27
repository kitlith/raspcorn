#include "peripheral.h"

#include "peripheral/gpio.h"

int peripheral_init(uc_engine *emu) {
    gpio_init(emu);
    return 0;
}
