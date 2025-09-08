// utils.c - Helper functions
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include "utils.h"

int utils_mkdir(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        if (mkdir(dir, 0700) != 0) {
            return -1;
        }
    }
    return 0;
}
