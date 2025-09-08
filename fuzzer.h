// fuzzer.h
#ifndef FUZZER_H
#define FUZZER_H
void fuzzer_run(const char *target, int runs, const char *seed_file, const char *output_dir, int timeout);
#endif
