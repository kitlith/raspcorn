#include "gpio.h"
#include "../uc_debug.h"

#include <unicorn/unicorn.h>
#include <inttypes.h>

#define UC_ENGINE_VAR emu

static void gpio_callback(uc_engine *emu, uc_mem_type type, uint64_t addr,
                        int size, uint64_t *value, void *nothing) {
    if ((type == UC_MEM_READ) || (type == UC_MEM_FETCH)) {
        *value = 0;
        printf(">>> GPIO Read at 0x%" PRIx64 ", size = 0x%x, return = 0x%lx\n",
                GPIO_BASE + addr, size, *value);
    }
    else if (type == UC_MEM_WRITE) {
        switch (addr) {
            case GPFSEL1:
                break;
            case GPSET0:
                if (*value & (1<<16)) {
                    puts("Status LED on!");
                }
                break;
            case GPCLR0:
                if (*value & (1<<16)) {
                    puts("Status LED off!");
                }
                break;
            default:
                printf(">>> GPIO Write at 0x%" PRIx64 ", size = 0x%x, value = 0x%lx\n",
                        GPIO_BASE + addr, size, *value);
                break;
        }
    }
}

int gpio_init(uc_engine *emu) {
    UC(mmio_map, GPIO_BASE, 0x1000, gpio_callback, NULL);
    return 0;
}

#undef UC_ENGINE_VAR
