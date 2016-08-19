// windows specific
#ifdef _MSC_VER
#include <io.h>
#include <windows.h>
#define PRIx64 "llX"
#ifdef DYNLOAD
#include "unicorn_dynload.h"
#else // DYNLOAD
#include <unicorn/unicorn.h>
#ifdef _WIN64
#pragma comment(lib, "unicorn_staload64.lib")
#else // _WIN64
#pragma comment(lib, "unicorn_staload.lib")
#endif // _WIN64
#endif // DYNLOAD

// posix specific
#else // _MSC_VER
#include <unistd.h>
#include <inttypes.h>
#include <unicorn/unicorn.h>
#endif // _MSC_VER

#include "uc_debug.h"

#define LOAD_ADDRESS 0x8000

#define UC_ENGINE_VAR emu

static bool hook_write(uc_engine *emu, uc_mem_type type, uint64_t addr,
                        uint32_t size, int64_t value, void* nothing) {
    printf(">>> Tracing write at 0x%" PRIx64 ", size = 0x%x\n", addr, size);
    return true;
}

int main(int argc, char **argv) {
    uc_engine *emu;
    const char code[] = "\x37\x00\xa0\xe3\x03\x10\x42\xe0"; // mov r0, #0x37; sub r1, r2, r3

    errorp(uc_open(UC_ARCH_ARM, UC_MODE_ARM, &emu), "uc_open");
    UC(mem_map,  0, 2*1024*1024, UC_PROT_ALL);
    UC(mem_write,  LOAD_ADDRESS, code, sizeof(code)-1);

    // Temp for testing.
    int r0 = 0x1234;     // R0 register
    int r2 = 0x6789;     // R1 register
    int r3 = 0x3333;     // R2 register

    UC(reg_write, UC_ARM_REG_R0, &r0);
    UC(reg_write, UC_ARM_REG_R2, &r2);
    UC(reg_write, UC_ARM_REG_R3, &r3);
    // End temp

    uc_hook hook;
    UC(hook_add, &hook, UC_HOOK_MEM_WRITE, (void*)hook_write, NULL, 1, 0);
    // That cast doesn't seem right...

    UC(emu_start, LOAD_ADDRESS, LOAD_ADDRESS+sizeof(code)-1, 0, 0);

    puts("Emulation Finished. CPU Context:");
    print_ctx(emu);

    return 0;
}

#undef UC_ENGINE_VAR
