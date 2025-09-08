# Simple Linux Fuzzer in C

## Overview
This is a modular, portable fuzzer written in C for Linux (Ubuntu/Debian). It generates random and mutated inputs, runs a target binary, and logs crashes.

## Features
- Random input generation and mutation (byte flip, insertion, deletion, ASCII/Unicode mix)
- Runs target via stdin, monitors for crashes (SIGSEGV, abnormal exit)
- Logs crashing inputs and metadata
- Configurable run count, timeout, output dir, and seed file
- Modular code: main.c, fuzzer.c, executor.c, logger.c, utils.c

## Build
```
make
```

## Usage
```
./fuzzer -p ./target_binary -n 1000 -s seed.txt -o crashes/ -t 2
```
- `-p <target_binary>`: Path to target binary (required)
- `-n <run_count>`: Number of runs (default 1000)
- `-s <seed_file>`: Seed input file (optional)
- `-o <output_dir>`: Directory to save crashes (default: crashes)
- `-t <timeout>`: Timeout per run in seconds (default: 2)

## Mutation Strategies
- **Byte flip**: Randomly flips a bit in the input
- **Insertion**: Inserts a random byte
- **Deletion**: Deletes a random byte
- **ASCII/Unicode mix**: Randomly replaces a byte with ASCII or Unicode

## Extending
- Add more mutation strategies in `fuzzer.c`
- Add coverage feedback in `executor.c`
- Improve logging/statistics in `logger.c`

## License
MIT
