#include "uc_debug.h"
#include <inttypes.h>
#include <ncurses.h>

void errorp(uc_err error, int lineno, const char* file, const char *func_name, uc_engine *emu) {
    if (error) {
        printf("%s() errored, and returned: %u (%s)\n",
                func_name, error, uc_strerror(error));
        print_ctx(emu);
        exit(-1);
    }
}

#define UC_ENGINE_VAR emu

static const int registers[] = { UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
                    UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
                    UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
                    UC_ARM_REG_R12, UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC };

void print_ctx(uc_engine *emu) {

    int64_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc;
    int64_t *reg_array[] = {&r0, &r1, &r2, &r3, &r4, &r5, &r6, &r7, &r8, &r9, &r10, &r11, &r12, &sp, &lr, &pc};
    // No error checking wrapper because this can be called from inside...
    // Don't want to infinitely loop and stackoverflow.
    // There is a way to read a bunch of registers at once! But is this everything...
    uc_reg_read_batch(emu, (int*)registers, (void**)reg_array, 16);
    printf( "R0 > 0x%016lx | R1 > 0x%016lx | R2 > 0x%016lx | R3 > 0x%016lx\n"
            "R4 > 0x%016lx | R5 > 0x%016lx | R6 > 0x%016lx | R7 > 0x%016lx\n"
            "R8 > 0x%016lx | R9 > 0x%016lx | R10> 0x%016lx | R11> 0x%016lx\n"
            "R12> 0x%016lx | SP > 0x%016lx | LR > 0x%016lx | PC > 0x%016lx\n",
            r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc);
}

#undef UC_ENGINE_VAR

// callback for tracing invalid memory access (READ/WRITE/EXEC)
// Thanks, unicorn examples.
bool hook_mem_invalid(uc_engine *uc, uc_mem_type type, uint64_t addr, int size,
    int64_t value, void *user_data) {
    switch(type) {
        default:
            printf(">>> UC_HOOK_MEM_INVALID type: %d at 0x%" PRIx64 "\n", type, addr);
            return false;
        case UC_MEM_READ_UNMAPPED:
            printf(">>> Read from invalid memory at 0x%" PRIx64 ", Size = %u\n", addr, size);
            return false;
        case UC_MEM_WRITE_UNMAPPED:
            printf(">>> Write to invalid memory at 0x%" PRIx64 ", Size = %u, Value = 0x%" PRIx64 "\n", addr, size, value);
            return false;
        case UC_MEM_FETCH_PROT:
            printf(">>> Fetch from non-executable memory at 0x%" PRIx64 "\n", addr);
            return false;
        case UC_MEM_WRITE_PROT:
            printf(">>> Write to non-writeable memory at 0x%" PRIx64 ", Size = %u, Value = 0x%" PRIx64 "\n", addr, size, value);
            return false;
        case UC_MEM_READ_PROT:
            printf(">>> Read from non-readable memory at 0x%" PRIx64 ", Size = %u\n", addr, size);
            return false;
    }
}
