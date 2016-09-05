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
#include <signal.h>

#include "uc_debug.h"
#include "args.h"
#include "peripheral.h"

#define UC_ENGINE_VAR emu

uc_engine *tmp; // Need a better way to do this!

void sigINT(int whocares) {
    puts("\nCPU Context:");
    print_ctx(tmp);
    exit(0);
}

int main(int argc, char **argv) {
    struct prog_options opt = {
        .load_addr = 0x8000,
        .peripheral_base = 0x20000000
    };
    parse_args(argc, argv, &opt);

    FILE *codefile;
    if (opt.bin_filename && !strcmp(opt.bin_filename, "-")) {
        codefile = stdin;
    } else if (opt.bin_filename) {
        codefile = fopen(opt.bin_filename, "rb");
        if (codefile == NULL) {
            puts("The file does not appear to exist!");
            exit(-1);
        }
    } else {
        exit(-1);
    }

    puts("\x28\x20\xcd\xa1\xc2\xb0\xcd\x9c\xca\x96\xcd\xa1\xc2\xb0\x29"); // ( ͡°͜ʖ͡°)

    uc_engine *emu;

    errorp(uc_open(UC_ARCH_ARM, UC_MODE_ARM, &emu), __LINE__, __FILE__, "uc_open", emu);
    UC(mem_map, 0, 2*1024*1024, UC_PROT_ALL);
    tmp = emu;
    signal(SIGINT, sigINT);

    char c = fgetc(codefile);
    unsigned int code_size = 0;
    while (!feof(codefile)) {
        UC(mem_write, opt.load_addr + (sizeof(char)*code_size), &c, sizeof(char));
        ++code_size;
        c = fgetc(codefile);
    }

    peripheral_init(emu, opt.peripheral_base);

    uc_hook invalid, read;
    UC(hook_add, &invalid, UC_HOOK_MEM_INVALID, (void*)hook_mem_invalid, NULL, 1, 0);
    // UC(hook_add, &read, UC_HOOK_MEM_READ, (void*)hook_mem_read, NULL, 1, 0);
    // That cast doesn't seem right...

    UC(emu_start, opt.load_addr, opt.load_addr + (sizeof(char)*code_size), 0, 0);

    puts("Emulation Finished. CPU Context:");
    print_ctx(emu);

    return 0;
}

#undef UC_ENGINE_VAR
