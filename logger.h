// logger.h
#ifndef LOGGER_H
#define LOGGER_H
#include <stddef.h>
void logger_log_crash(const char *output_dir, const unsigned char *input, size_t len, int exit_status, int signal);
#endif
