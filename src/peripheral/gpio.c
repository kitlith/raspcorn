#include "gpio.h"
#include "../uc_debug.h"

#include <unicorn/unicorn.h>
#include <inttypes.h>

#define UC_ENGINE_VAR emu

// static struct gpioPin pins[54];
static const uint8_t testCmds[] = {
    0x9F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned testPos;
static unsigned dataPos;

static void gpio_callback(uc_engine *emu, uc_mem_type type, uint64_t addr,
                        int size, uint64_t *value, void *nothing) {
    if ((type == UC_MEM_READ) || (type == UC_MEM_FETCH)) {
        switch (addr) {
            case GPLEV0:
                if (testPos < sizeof(testCmds)) {
                    printf("CMDByte: 0x%02x\n", testCmds[testPos]);
                    *value = testCmds[testPos++] << 2;
                    dataPos = 0;
                }
                break;
            case GPEDS0:
                // puts("Checked pin status!");
                *value = (1 << 10) | ((dataPos >= 0x20) << 11);
                if (dataPos > 0x20) dataPos = 0;
                break;
        }
        // *value = 0;
        // printf(">>> GPIO Read at 0x%" PRIx64 ", size = 0x%x, return = 0x%lx\n",
        //         GPIO_BASE + addr, size, *value);
    }
    else if (type == UC_MEM_WRITE) {
        switch (addr) {
            // case GPFSEL1:
            //     for (unsigned pinno = 0; pinno < 10; ++pinno) {
            //         pins[pinno].function = (enum gpioFunction)((*value >> (pinno*3)) & 0b111);
            //     }
            //     printf(">>> GFPSEL1 == 0x%" PRIx64 "\n", *value);
            //     break;
            case GPSET0:
                printf("0x%02x\n", (unsigned char)(*value >> 2));
                ++dataPos;
                break;
            case GPCLR0:
                // if (*value & (1<<16)) {
                //     puts("Status LED off!");
                // }
                break;
            default:
                // printf(">>> GPIO Write at 0x%" PRIx64 ", size = 0x%x, value = 0x%lx\n",
                //         GPIO_BASE + addr, size, *value);
                break;
        }
    }
}

int gpio_init(uc_engine *emu, uint64_t peripheral_base) {
    UC(mmio_map, peripheral_base + GPIO_BASE, 0x1000, gpio_callback, NULL);
    return 0;
}

#undef UC_ENGINE_VAR
