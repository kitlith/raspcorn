#include "aux.h"
#include "../uc_debug.h"

static void aux_callback(uc_engine *emu, uc_mem_type type, uint64_t addr,
                        int size, uint64_t *value, void *nothing) {
    if ((type == UC_MEM_READ) || (type == UC_MEM_FETCH)) {

    } else if (type == UC_MEM_WRITE) {
        switch (addr) {
            case 0: break;
        }
    }
}

int aux_init(uc_engine *emu) {
    UC(mmio_map, AUX_BASE, 0x1000, aux_callback, NULL);
    return 0;
}
