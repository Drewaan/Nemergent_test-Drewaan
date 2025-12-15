# Entropy - Multithreaded Random Number Generator

## Description

**Entropy** is a C program that generates random numbers using multiple threads. The program creates a configurable number of worker threads, where each thread generates a specific amount of random integers. The generated numbers are automatically classified into two categories:

- **Positives**: Numbers greater than or equal to zero
- **Negatives**: Numbers less than zero

The program uses mutex synchronization to ensure thread-safe access to shared data structures (buckets).

## Features

- Parallel random number generation using `pthread`
- Automatic classification of numbers into positives and negatives
- Dynamic buckets that grow on demand
- Thread-safe synchronization with mutex
- Ascending order sorting of results

## Requirements

- GCC (GNU Compiler Collection)
- pthread library (usually included in Linux/Unix systems)
- Make

## Compilation

To compile the project, run from the root directory:

```bash
make
```

This will generate the `entropy` executable in the current directory.

### Other Make Commands

| Command      | Description                                    |
|--------------|------------------------------------------------|
| `make`       | Compiles the project                           |
| `make all`   | Same as `make`                                 |
| `make clean` | Removes object files and the binary executable |

## Usage

```bash
./entropy <nthreads> <per_thread>
```

### Parameters

| Parameter     | Description                                              |
|---------------|----------------------------------------------------------|
| `nthreads`    | Total number of threads to create (must be > 0)          |
| `per_thread`  | Amount of numbers each thread generates (must be > 0)    |

### Examples

```bash
# Create 1 thread that generates 1 number
./entropy 1 1

# Create 10 threads, each generates 10 numbers (100 numbers total)
./entropy 10 10

# Create 100 threads, each generates 100 numbers (10,000 numbers total)
./entropy 100 100
```

### Output

The program displays a summary of the generated values:

```
=== SUMMARY OF GENERATED VALUES ===

→ List of numbers greater than or equal to zero:
   [  0]  12345678
   [  1]  98765432
   ...

→ List of numbers less than zero:
   [  0]  -12345678
   [  1]  -87654321
   ...
```

## Using the Test Script (test.sh)

The project includes an interactive test script located at `tests/test.sh`.

### Running the Script

```bash
# From the project root directory
cd tests
bash test.sh
```

Or alternatively:

```bash
# From the root directory (make sure the executable is compiled)
bash tests/test.sh
```

> **Note**: The script expects the `entropy` executable to be in the directory from which the script is run. If you run the script from `tests/`, make sure to copy or link the executable there, or modify the `EXEC` variable in the script.

### Test Menu

The script presents an interactive menu with the following options:

| Option | Description                                      |
|--------|--------------------------------------------------|
| 1      | No parameters (error test)                       |
| 2      | Single parameter (error test)                    |
| 3      | First parameter is not numeric (error test)      |
| 4      | Second parameter is not numeric (error test)     |
| 5      | Number of threads = 0 (error test)               |
| 6      | Amount per thread = 0 (error test)               |
| 7      | Small test (1 thread, 1 number)                  |
| 8      | Medium test (10 threads, 10 numbers)             |
| 9      | Large test (100 threads, 100 numbers)            |
| 0      | Exit tester                                      |

### Tester Usage Example

```
===== TESTER MENU =====
1) No parameters
2) Single parameter
3) First parameter is not numeric
4) Second parameter is not numeric
5) Number of threads = 0
6) Amount per thread = 0
7) Small test (1 thread, 1 number)
8) Medium test (10 threads, 10 numbers)
9) Large test (100 threads, 100 numbers)
0) Exit

Select test: 7
```

## Project Structure

```
.
├── Makefile                    # Build file
├── README.md                   # This file
├── include/
│   └── entropy.h               # Main header with structures and prototypes
├── src/
│   ├── main.c                  # Program entry point
│   ├── bucket/
│   │   ├── bucket_init.c       # Bucket initialization
│   │   ├── bucket_ops.c        # Bucket operations (push)
│   │   └── bucket_utils.c      # Utilities (destroy, compact, sort)
│   ├── display/
│   │   └── results_display.c   # Display results on screen
│   ├── workers/
│   │   ├── random_gen.c        # Random number generation
│   │   └── thread_worker.c     # Worker thread logic
│   └── world/
│       ├── world_init.c        # "World" initialization
│       └── world_ops.c         # Final operations and cleanup
└── tests/
    └── test.sh                 # Interactive test script
```

## Architecture

### Data Structures

- **`bucket_t`**: Dynamic container for storing integers with mutex for synchronization
- **`world_t`**: Main structure containing configuration and positive/negative buckets

### Program Flow

1. Argument validation
2. "World" initialization (buckets and mutex)
3. Creation of N worker threads
4. Each thread generates M random numbers and classifies them
5. Wait for all threads to finish
6. Sort buckets
7. Display results
8. Memory cleanup
