#pragma once

#ifndef RASPCORN_ARGS
#define RASPCORN_ARGS

#include <getopt.h>
#include <stdint.h>

struct prog_options {
    uint64_t load_addr;
    uint64_t peripheral_base;
    char **extra_args;
    unsigned int extra_argc;
    char *bin_filename;
};

void parse_args(int argc, char **argv, struct prog_options *opt);

#endif /* end of include guard: RASPCORN_ARGS */
