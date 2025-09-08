// fuzzer.c - Input generation and mutation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fuzzer.h"
#include "executor.h"
#include "logger.h"
#include "utils.h"

#define MAX_INPUT_SIZE 4096

static void mutate_input(unsigned char *buf, size_t *len) {
    int mutation = rand() % 3;
    size_t pos = rand() % (*len);
    switch (mutation) {
        case 0: // Byte flip
            buf[pos] ^= (1 << (rand() % 8));
            break;
        case 1: // Random insertion
            if (*len < MAX_INPUT_SIZE - 1) {
                memmove(buf + pos + 1, buf + pos, *len - pos);
                buf[pos] = (unsigned char)(rand() % 256);
                (*len)++;
            }
            break;
        case 2: // Random deletion
            if (*len > 1) {
                memmove(buf + pos, buf + pos + 1, *len - pos - 1);
                (*len)--;
            }
            break;
    }
    // ASCII/Unicode mix
    if (rand() % 2) {
        buf[rand() % (*len)] = (rand() % 2) ? (rand() % 128) : (rand() % 0x10000);
    }
}

static size_t load_seed(const char *seed_file, unsigned char *buf) {
    if (!seed_file) {
        // Default: random string
        size_t len = 32 + rand() % 32;
        for (size_t i = 0; i < len; i++)
            buf[i] = (unsigned char)(rand() % 256);
        return len;
    }
    FILE *f = fopen(seed_file, "rb");
    if (!f) return 0;
    size_t len = fread(buf, 1, MAX_INPUT_SIZE, f);
    fclose(f);
    return len;
}

void fuzzer_run(const char *target, int runs, const char *seed_file, const char *output_dir, int timeout) {
    srand(time(NULL));
    unsigned char input[MAX_INPUT_SIZE];
    size_t input_len = load_seed(seed_file, input);
    if (input_len == 0) input_len = 16;
    int crash_count = 0;
    for (int i = 0; i < runs; i++) {
        size_t cur_len = input_len;
        unsigned char buf[MAX_INPUT_SIZE];
        memcpy(buf, input, cur_len);
        mutate_input(buf, &cur_len);
        int exit_status, signal;
        int result = executor_run(target, buf, cur_len, timeout, &exit_status, &signal);
        if (result == EXECUTOR_CRASH) {
            logger_log_crash(output_dir, buf, cur_len, exit_status, signal);
            crash_count++;
        }
    }
    printf("Fuzzing done. Total runs: %d, Crashes: %d\n", runs, crash_count);
}
