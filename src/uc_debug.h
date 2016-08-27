#pragma once

#ifndef RASPCORN_UC_DEBUG
#define RASPCORN_UC_DEBUG

#include <unicorn/unicorn.h>

void errorp(uc_err error, int lineno, const char* file,
            const char *func_name, uc_engine *emu);

void print_ctx(uc_engine *emu);

bool hook_mem_invalid(uc_engine *uc, uc_mem_type type, uint64_t addr, int size,
    int64_t value, void *user_data);

// This uses a define, UC_ENGINE_VAR, so that I'm not hardcoding 'emu', though
// that will probably be the variable name in most cases.
#define UC(func, ...) errorp(uc_##func(UC_ENGINE_VAR, __VA_ARGS__), __LINE__, __FILE__, "uc_" #func, UC_ENGINE_VAR);

#endif /* end of include guard: RASPCORN_UC_DEBUG */
