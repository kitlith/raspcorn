#include "args.h"
#include <string.h>
#include <stdio.h>

static struct option longopts[] = {
    {0,0,0,0}
};

void parse_args(int argc, char **argv, struct prog_options *opt) {
    memset(opt, 0, sizeof(*opt));
    char c;
    while ((c = getopt_long(argc, argv, "", longopts, 0)) != -1) {
        switch(c) {
            case '?':
                break; // error already handled
        } // TODO: Actually add options.
    }
    unsigned int nonoptions = argc - optind;
    if (nonoptions > 0) {
        opt->bin_filename = argv[optind]; --nonoptions;
        if (nonoptions > 0){
            opt->extra_args = argv + (sizeof(*argv) * optind);
            opt->extra_argc = argc - optind - 1;
        }
    } else {
        puts("Not enough arguments! Pass a filename, or '-' for stdin.");
    }
}
