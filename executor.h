// executor.h
#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <stddef.h>
#define EXECUTOR_OK 0
#define EXECUTOR_CRASH 1
#define EXECUTOR_ERROR -1
int executor_run(const char *target, const unsigned char *input, size_t len, int timeout, int *exit_status, int *signal_out);
#endif
