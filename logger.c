// logger.c - Saves crashes and metadata
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logger.h"

void logger_log_crash(const char *output_dir, const unsigned char *input, size_t len, int exit_status, int signal) {
    char filename[512];
    time_t t = time(NULL);
    snprintf(filename, sizeof(filename), "%s/crash_%ld_%d_%d.bin", output_dir, t, exit_status, signal);
    FILE *f = fopen(filename, "wb");
    if (!f) return;
    fwrite(input, 1, len, f);
    fclose(f);
    // Log metadata
    snprintf(filename, sizeof(filename), "%s/crash_%ld_%d_%d.txt", output_dir, t, exit_status, signal);
    f = fopen(filename, "w");
    if (!f) return;
    fprintf(f, "Exit status: %d\nSignal: %d\nInput length: %zu\n", exit_status, signal, len);
    fclose(f);
}
