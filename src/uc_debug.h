#pragma once

#ifndef RASPCORN_UC_DEBUG
#define RASPCORN_UC_DEBUG

#include <unicorn/unicorn.h>

void errorp(uc_err error, const char *func_name);

void print_ctx(uc_engine *emu);

// This uses a define, UC_ENGINE_VAR, so that I'm not hardcoding 'emu', though
// that will probably be the variable name in most cases.
#define UC(func, ...) errorp(uc_##func(UC_ENGINE_VAR, __VA_ARGS__), "uc_" #func)

#endif /* end of include guard: RASPCORN_UC_DEBUG */
