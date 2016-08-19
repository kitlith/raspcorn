#include "uc_debug.h"
void errorp(uc_err error, const char *func_name) {
    if (error) {
        printf("%s() errored, and returned: %u (%s)\n",
                func_name, error, uc_strerror(error));
        exit(-1);
    }
}

#define UC_ENGINE_VAR emu

void print_ctx(uc_engine *emu) {
    int r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc;
    UC(reg_read, UC_ARM_REG_R0, &r0);
    UC(reg_read, UC_ARM_REG_R1, &r1);
    UC(reg_read, UC_ARM_REG_R2, &r2);
    UC(reg_read, UC_ARM_REG_R3, &r3);
    UC(reg_read, UC_ARM_REG_R4, &r4);
    UC(reg_read, UC_ARM_REG_R5, &r5);
    UC(reg_read, UC_ARM_REG_R6, &r6);
    UC(reg_read, UC_ARM_REG_R7, &r7);
    UC(reg_read, UC_ARM_REG_R8, &r8);
    UC(reg_read, UC_ARM_REG_R9, &r9);
    UC(reg_read, UC_ARM_REG_R10, &r10);
    UC(reg_read, UC_ARM_REG_R11, &r11);
    UC(reg_read, UC_ARM_REG_R12, &r12);
    UC(reg_read, UC_ARM_REG_SP, &sp);
    UC(reg_read, UC_ARM_REG_LR, &lr);
    UC(reg_read, UC_ARM_REG_PC, &pc);
    printf( "R0 > 0x%08x | R1 > 0x%08x | R2 > 0x%08x | R3 > 0x%08x\n"
            "R4 > 0x%08x | R5 > 0x%08x | R6 > 0x%08x | R7 > 0x%08x\n"
            "R8 > 0x%08x | R9 > 0x%08x | R10> 0x%08x | R11> 0x%08x\n"
            "R12> 0x%08x | SP > 0x%08x | LR > 0x%08x | PC > 0x%08x\n",
            r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc);
}

#undef UC_ENGINE_VAR
