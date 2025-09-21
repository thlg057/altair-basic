# BASIC Interpreter (C Implementation)

## Overview
This project is a lightweight **BASIC interpreter written in C**, inspired by the original **Altair BASIC** implementation of Bill Gates and Paul Allen in the 1970s. Altair BASIC was the first Microsoft product and one of the first BASIC interpreters for microcomputers, originally developed for the Altair 8800.

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
- `repl.c/.h` → handles program lifecycle and REPL execution.
- `program.c/.h` → manages storage of BASIC program lines.
- `memory.c/.h` → variable storage and evaluation.
- `token.c/.h` → breaks a raw line of BASIC code (string) into smaller pieces (tokens).
- `interpreter.c/.h` → parses and executes BASIC commands.
- `parser.c/.h` → interpret parameters.

---

## Supported BASIC Keywords (V1 Compatibility)

This interpreter supports the **keywords and syntax of the early Microsoft BASIC** (circa 1975).  

### Program Control
- ✅`RUN` → execute the loaded program.  
- ✅`LIST` → display the current program.  
- ✅`NEW` → clear program memory.  
- ✅`STOP` → stop execution.  
- ✅`END` → terminate program execution.  

### Input/Output
- ✅`PRINT <expr>` → output expression(s) to console.  
- ✅`INPUT <var>` → read value from user input.  

### Variables & Expressions
- ✅Numeric variables (`A`, `X1`).  
- ✅Assignment with `LET` (`LET A=5`).  
- ✅Basic arithmetic operators: `+`, `-`, `*`, `/`.  

### Control Flow
- ✅`IF <expr> THEN <line>` → conditional branching.  
- ✅`GOTO <line>` → jump to a program line.  
- ~~⏳`GOSUB <line>` / `RETURN` → subroutine calls.~~
- ✅`FOR <var>=<start> TO <end> [STEP <n>]` → loops.  
- ✅`NEXT <var>` → end of loop.  

---

## Historical Context: Altair BASIC

This interpreter pays homage to **Altair BASIC**, the legendary programming language that launched Microsoft in 1975. Originally written by Bill Gates and Paul Allen for the MITS Altair 8800, Altair BASIC was revolutionary for several reasons:

- **First commercial BASIC for microcomputers**: Made programming accessible to hobbyists and small computer users.
- **Efficient memory usage**: Designed to run in just 4KB of RAM, showcasing extreme optimization techniques.
- **Foundation of Microsoft**: This interpreter became Microsoft's first product and established the company's software licensing model.
- **Influenced the industry**: Set the standard for BASIC implementations on early personal computers.

Our implementation aims to capture the **minimalist spirit** and **architectural elegance** of that pioneering software, while adapting it for modern C development practices.

---

## Error Handling
All functions return a `ResultCode`:
```c
typedef enum {
    RESULT_OK = 0,
    RESULT_PRG_STOPPED = -1,
    RESULT_UNKNOW_ERROR = -2,
    RESULT_ERROR = -3,
    RESULT_SYNTAX_ERROR = -4,
    RESULT_MEMORY_CAPACITY_ERROR = -5,
    RESULT_STRING_CAPACITY_ERROR = -6,
    RESULT_LINE_NOT_FOUND_ERROR = -7
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

Check binary size:
```bash
make size
```

Clean build:
```bash
make clean
```

---

## Size Comparison: Then and Now

Our BASIC interpreter achieves compact size through careful optimization:

```
----- Binary size -----
   text    data     bss     dec     hex filename
  16640    5040     336   22016    5600 bin/basic.exe
Total size in KB: 21.50 KB
```

**Historical Reference**: The original Altair BASIC by Bill Gates and Paul Allen ran in just 4KB of RAM and was written entirely in **8080 assembly language** for maximum efficiency. This modern implementation, written in **C**, naturally requires more space due to:

- **Language overhead**: C compiler generates more instructions than hand-optimized assembly
- **Modern executable format**: Headers, symbol tables, and runtime requirements
- **Enhanced error handling** and **comprehensive validation**
- **Portability across platforms** rather than single-target optimization

This implementation follows similar **minimalist design principles**:
- **Custom mini-functions** replace standard library calls where possible
- **Careful memory management** with fixed-size structures  
- **Efficient parsing algorithms** with minimal overhead
- **Modular architecture** prevents code bloat

At 21.50 KB, this demonstrates that classic minimalist approaches remain valuable, even when trading assembly's raw efficiency for C's maintainability and portability.

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
```basic
10 LET A = 10
20 GOTO 40
30 LET A = 20
40 IF A = 10 THEN 70
50 PRINT "round 2: " + A
60 END
70 PRINT "round 1: " + A
80 GOTO 30
RUN
```

Output:
```
round 1: 10
round 2: 20
```
---

## Roadmap
- ✅ Core interpreter structure  
- ✅ REPL loop  
- ✅ Error handling system  
- ✅ Variable management  
- ✅ Parser and execution engine

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
