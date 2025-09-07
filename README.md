# BASIC Interpreter (C Implementation)

## Overview
This project is a lightweight **BASIC interpreter written in C**, inspired by the original implementation of Bill Gates and Paul Allen in the 1970s.  

The main objectives are:
- Stay close to the **minimalistic philosophy** of early microcomputer interpreters.  
- Provide a **low memory footprint** and efficient design suitable for constrained systems.  
- Follow **strict C coding practices** (C89/C90 style, portable, modular).  
- Offer a **clean architecture** with separate modules for interpreter, variables, program storage, utilities, and error handling.  
- Include a **test suite** to validate the interpreter’s correctness.  

---

## Goals
- Implement a **working BASIC interpreter** supporting the original syntax and keywords.  
- Provide an **interactive REPL** (Read-Eval-Print Loop).  
- Allow **loading, running, and stopping programs** written in BASIC.  
- Keep the design **simple and modular**, with `.c` and `.h` separation.  
- Respect best practices:  
  - Functions return `0` on success or a negative `ResultCode` on error.  
  - `ResultCode` enumeration centralizes all error codes.  
  - Consistent **camelCase naming** for variables and functions.  

---

## Project Structure
```
src/            # Interpreter source code (.c and .h)
tests/          # Unit tests
build/          # Object files
bin/            # Compiled binaries
Makefile        # Build system
```

Main modules:
- `main.c` → entry point, starts the REPL.
- `common.h` → provides inline helper functions for strings, printing, and validation.
- `error.c/.h` → error codes and string conversion.
- `basic_repl.c/.h` → handles program lifecycle and REPL execution.
- `program.c/.h` → manages storage of BASIC program lines.
- `memory.c/.h` → variable storage and evaluation.
- `token.c/.h` → breaks a raw line of BASIC code (string) into smaller pieces (tokens).
- `interpreter.c/.h` → parses and executes BASIC commands.

---

## Supported BASIC Keywords (V1 Compatibility)

This interpreter supports the **keywords and syntax of the early Microsoft BASIC** (circa 1975).  

### Program Control
- `RUN` → execute the loaded program.  
- `LIST` → display the current program.  
- `NEW` → clear program memory.  
- `STOP` → stop execution.  
- `END` → terminate program execution.  

### Input/Output
- `PRINT <expr>` → output expression(s) to console.  
- `INPUT <var>` → read value from user input.  

### Variables & Expressions
- Integer and string variables (`A`, `X1`, `STR$`).  
- Assignment with `LET` (optional, `LET A=5` or `A=5`).  
- Basic arithmetic operators: `+`, `-`, `*`, `/`.  

### Control Flow
- `IF <expr> THEN <line>` → conditional branching.  
- `GOTO <line>` → jump to a program line.  
- `GOSUB <line>` / `RETURN` → subroutine calls.  
- `FOR <var>=<start> TO <end> [STEP <n>]` → loops.  
- `NEXT <var>` → end of loop.  

---

## Error Handling
All functions return a `ResultCode`:
```c
typedef enum {
    RESULT_OK = 0,
    RESULT_ERROR = -1,
    RESULT_MEMORY_CAPACITY_ERROR = -2,
    RESULT_STRING_CAPACITY_ERROR = -3,
    RESULT_PRG_STOPPED = -4
} ResultCode;
```

Errors are automatically mapped to human-readable messages (e.g., `"Memory capacity exceeded"`).  

---

## Building the Project

Requirements:
- GCC or Clang
- Make

Build release binary:
```bash
make
```

Build debug binary (with warnings and symbols):
```bash
make debug
```

Run tests:
```bash
make test
```

Clean build:
```bash
make clean
```

---

## Example Session

```basic
10 PRINT "HELLO WORLD"
20 FOR I = 1 TO 5
30 PRINT I
40 NEXT I
RUN
```

Output:
```
HELLO WORLD
1
2
3
4
5
```

---

## Roadmap
- ✅ Core interpreter structure  
- ✅ REPL loop  
- ✅ Error handling system  
- ✅ Variable management  
- ⏳ Parser and execution engine  
- ⏳ String manipulation functions (`LEFT$`, `RIGHT$`, `MID$`)  
- ⏳ File I/O commands  

---

### AI Assistance

During the development of this minimal BASIC interpreter, AI tools were leveraged to:

- Analyze the project and suggest optimizations to reduce the binary size.
- Propose a lightweight implementation for core functions, minimizing dependencies on the standard library.
- Recommend strategies for replacing `printf` and `strcasecmp` with smaller, custom alternatives.
- Help structure the project files and Makefile for efficient compilation and testing.

These AI-assisted recommendations contributed to a significantly smaller executable, aligning with the historical goal of creating a compact BASIC interpreter, while maintaining clarity and maintainability of the code.

---

## License
This project is distributed under the **MIT License**.  
It is a personal educational project to explore **retrocomputing techniques and C best practices**.  
