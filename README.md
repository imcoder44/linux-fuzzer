# linux-fuzzer

A modular, extensible Linux-based fuzzer written in C.  
This tool is designed to fuzz arbitrary binaries by generating and mutating inputs, executing the target, and logging any crashes or abnormal behaviors.

---

## Features

- **Modular C codebase**: Easy to extend and maintain.
- **Random input generation and mutation**: Supports byte flipping, insertions/deletions, ASCII/Unicode mixing.
- **Target execution isolation**: Uses `fork()` and `execv()` to safely run the target binary.
- **Crash detection**: Detects segmentation faults and abnormal exits.
- **Crash logging**: Saves crashing inputs and metadata to a specified directory.
- **Seed file support**: Start fuzzing from a known input.
- **Configurable runs**: Specify number of fuzzing iterations.
- **Easy build and usage**: Standard Makefile and clear CLI.

---

## Directory Structure

```
linux-fuzzer/
├── Makefile
├── README.md
├── seed.txt
├── target_example.c
├── src/
│   ├── main.c
│   ├── fuzz.c
│   ├── fuzz.h
│   ├── utils.c
│   ├── utils.h
```

---

## Build Instructions

1. **Clone or download the repository.**
2. **Build the fuzzer:**
   ```sh
   make
   ```
3. **Build the example target (or your own target):**
   ```sh
   gcc -o target_example target_example.c
   ```

---

## Usage

```sh
./linux-fuzzer -p <target_binary> -n <runs> -s <seed_file> -o <output_dir>
```

**Example:**
```sh
./linux-fuzzer -p ./target_example -n 1000 -s seed.txt -o crashes/
```

**Arguments:**
- `-p <target_binary>`: Path to the target executable to fuzz.
- `-n <runs>`: Number of fuzzing iterations.
- `-s <seed_file>`: Path to a seed input file.
- `-o <output_dir>`: Directory to save crash-inducing inputs.

---

## Example Target

A simple C program (`target_example.c`) is provided for demonstration.  
It crashes if the input string is `"crashme"`.

Build it with:
```sh
gcc -o target_example target_example.c
```

---

## Mutation Strategies

- **Random Byte Flipping:** Randomly flips bits or bytes in the input.
- **Random Insertions/Deletions:** Inserts or removes random bytes.
- **ASCII/Unicode Mix:** Mixes printable ASCII and Unicode characters.

You can extend `src/fuzz.c` to implement and combine these strategies.

---

## How It Works

1. **Initialization:** Loads the seed file and parses arguments.
2. **Mutation:** Generates mutated inputs based on the seed.
3. **Execution:** Runs the target binary with mutated input (via command-line or stdin).
4. **Crash Detection:** Monitors for crashes (e.g., SIGSEGV) and abnormal exits.
5. **Logging:** Saves crashing inputs and metadata to the output directory.
6. **Statistics:** Prints summary after fuzzing (runs, crashes, etc.).

---

## Extending the Fuzzer

- **Add new mutation strategies** in `src/fuzz.c`.
- **Implement coverage feedback** (optional, via `ptrace` or `LD_PRELOAD`).
- **Improve logging** in `src/utils.c` or add a dedicated logger module.
- **Support more input formats** (e.g., files, network).

---

## Troubleshooting

- If you see `No such file or directory`, ensure you are in the correct directory and have built the binaries.
- If you get linker errors, make sure all required functions are implemented and source files are included in the Makefile.

---

## License

MIT License

---

## Credits

Inspired by classic fuzzers and educational projects.  
Feel free to contribute or suggest improvements!
