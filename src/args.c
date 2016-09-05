#include "args.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static struct option longopts[] = {
    {"load_address", required_argument, NULL, 'l'},
    {"peripherals", required_argument, NULL, 'p'},
    {0,0,0,0}
};

void parse_args(int argc, char **argv, struct prog_options *opt) {
    memset(opt, 0, sizeof(*opt));
    char c;
    while ((c = getopt_long(argc, argv, "lp", longopts, 0)) != -1) {
        switch(c) {
            case 'l':
                if (optarg != NULL) {
                    opt->load_addr = strtol(optarg, NULL, 0);
                } else exit(EXIT_FAILURE);
                break;
            case 'p':
                if (optarg != NULL){
                    opt->peripheral_base = strtol(optarg, NULL, 0);
                } else exit(EXIT_FAILURE);
                break;
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
