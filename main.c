// main.c - Entry point and argument parsing for the fuzzer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzzer.h"
#include "executor.h"
#include "logger.h"
#include "utils.h"

void print_usage(const char *prog) {
    printf("Usage: %s -p <target_binary> [-n run_count] [-s seed_file] [-o output_dir] [-t timeout]\n", prog);
}

int main(int argc, char *argv[]) {
    char *target_path = NULL;
    char *seed_file = NULL;
    char *output_dir = "crashes";
    int run_count = 1000;
    int timeout = 2;
    int opt;

    // Simple argument parsing
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            target_path = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            run_count = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            seed_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_dir = argv[++i];
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            timeout = atoi(argv[++i]);
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }

    if (!target_path) {
        print_usage(argv[0]);
        return 1;
    }

    if (utils_mkdir(output_dir) != 0) {
        fprintf(stderr, "Failed to create output directory: %s\n", output_dir);
        return 1;
    }

    fuzzer_run(target_path, run_count, seed_file, output_dir, timeout);
    return 0;
}
