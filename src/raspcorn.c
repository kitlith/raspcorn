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

#include <stdio.h>
#include <string.h>

#include "uc_debug.h"
#include "args.h"

#define LOAD_ADDRESS 0x8000

#define UC_ENGINE_VAR emu

static bool hook_write(uc_engine *emu, uc_mem_type type, uint64_t addr,
                        uint32_t size, int64_t value, void* nothing) {
    printf(">>> Tracing write at 0x%" PRIx64 ", size = 0x%x\n", addr, size);
    return true;
}

int main(int argc, char **argv) {
    struct prog_options opt;
    parse_args(argc, argv, &opt);

    FILE *codefile;
    if (opt.bin_filename && strcmp(opt.bin_filename, "-")) {
        codefile = stdin;
    } else if (opt.bin_filename) {
        codefile = fopen(opt.bin_filename, "rb");
    } else {
        exit(-1);
    }

    uc_engine *emu;

    errorp(uc_open(UC_ARCH_ARM, UC_MODE_ARM, &emu), "uc_open");
    UC(mem_map,  0, 2*1024*1024, UC_PROT_ALL);
    puts("Emulator memory mapped..."); //debug

    char c;
    unsigned int code_size = 0;
    while ((c = fgetc(codefile)) != EOF) {
        puts("Read a byte!"); //debug
        UC(mem_write,  LOAD_ADDRESS + (sizeof(char)*code_size), &c, sizeof(char));
        ++code_size;
    }
    puts("Read file into emulator memory..."); //debug

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

    UC(emu_start, LOAD_ADDRESS, LOAD_ADDRESS + (sizeof(char)*code_size) - 1, 0, 0);

    puts("Emulation Finished. CPU Context:");
    print_ctx(emu);

    return 0;
}

#undef UC_ENGINE_VAR
