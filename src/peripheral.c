#include "peripheral.h"

#include "peripheral/gpio.h"

int peripheral_init(uc_engine *emu, uint64_t peripheral_base) {
    gpio_init(emu, peripheral_base);
    return 0;
}
