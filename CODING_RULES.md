# Coding Rules – BASIC Interpreter (C)

## Objective
This project aims to develop a **minimalist BASIC interpreter in C**, inspired by the early work of Bill Gates and Paul Allen. The goal is to maintain a **very small memory footprint** and a **compact codebase**, prioritizing simplicity and reliability over raw performance.

These rules ensure consistency, maintainability, and robustness across the project.

---

## 1. General Rules
- Code must be **readable, simple, and compact**.  
- **No unnecessary external dependencies** (stick to the standard C library).  
- Priority is given to **memory efficiency** over speed.  
- All functions must return a `ResultCode`:  
  - `RESULT_OK (0)` on success  
  - Negative `ResultCode` on error  
- All error codes must be **explicitly checked** after critical calls.  
- No implicit assumptions: **errors must always be handled explicitly**.  

---

## 2. Result Codes and Error Handling
```c
typedef enum {
    RESULT_OK = 0,
    RESULT_ERROR = -1,
    RESULT_MEMORY_CAPACITY_ERROR = -2,
    RESULT_STRING_CAPACITY_ERROR = -3,
    RESULT_PRG_STOPPED = -4
} ResultCode;
```

### Rules:
- Functions **must not return raw pointers** to indicate errors. Always return a `ResultCode`.  
- Output values (pointers, integers, etc.) are passed by reference (via parameters).  
- On error, all allocated resources must be released before returning.  

---

## 3. Project Structure
- Each module must have a `.h` and `.c` file.  
  - Example: `lexer.h` / `lexer.c`  
- Exception: `main.c` (no header).  
- Header files contain:  
  - Public declarations (`struct`, `enum`, `typedef`, function prototypes)  
  - No logic in headers (only minimal inline macros if absolutely necessary).  

---

## 4. Naming Conventions
- **camelCase** for functions and variables:  
  ```c
  int parseLine(const char *line);
  int lineNumber;
  ```
- **UPPERCASE_SNAKE_CASE** for constants and macros:  
  ```c
  #define MAX_LINE_LENGTH 256
  ```
- File names must match the module name:  
  - `lexer.c`, `parser.c`, `memory.c`...  

---

## 5. Memory Management
- **No uncontrolled malloc/free usage.**  
- Prefer **static allocation** or pre-allocated buffers.  
- Maximum sizes (lines, tokens, program size) must be defined using `#define`.  
- Always check buffer capacity before writing.  

Example:
```c
if (index >= MAX_TOKENS) {
    return RESULT_MEMORY_CAPACITY_ERROR;
}
```

---

## 6. Code Style
- Indentation: **4 spaces** (no tabs).  
- Braces are **always required**, even for single statements.  
- One function = one responsibility.  
- Maximum function length: **40 lines** (refactor if longer).  
- No global variables, except constants (`const` or `#define`).  

---

## 7. String Handling
- Strings must always use **fixed-size buffers**.  
- All string operations must check boundaries.  
- Avoid unsafe functions like `strcpy`/`strcat` → use `strncpy`/`strncat`.  

---

## 8. Compilation and Portability
- The project must compile with `-Wall -Wextra -pedantic` **without warnings**.  
- Target: **C89/C90** (avoid modern extensions).  
- Code must be portable across 16‑bit and 32‑bit systems.  

---

## 9. Documentation & Comments
- Each function must have a **header comment**:
  ```c
  /**
   * Parse a BASIC line.
   * @param line Input line
   * @return ResultCode
   */
  ResultCode parseLine(const char *line);
  ```
- Comments should explain **why**, not **how** (the code already shows how).  

---

## 10. Testing & Validation
- Each module must be independently testable.  
- Always test error cases (`NULL`, overflow, capacity reached, etc.).  
- The program must always terminate cleanly (`RESULT_PRG_STOPPED`).  

---

## 11. BASIC Philosophy
This interpreter follows the **early BASIC philosophy**:

- **Line-by-line execution** (interpreted as typed, no compilation).  
- **Minimal memory footprint**, mirroring early microcomputer limitations (≈4 KB).  
- **REPL design**:
  - Immediate mode for commands.
  - Program mode with numbered lines and storage.
- **No unnecessary complexity**—focus on clarity and memory efficiency.  
- **Simple design** that could run on 8‑ or 16‑bit systems.

---

## 12. Supported BASIC Keywords / Syntax (Altair BASIC v1)

#### 4K BASIC Reserved Keywords:
```
ABS, CLEAR, DATA, DIM, END, FOR, GOSUB, GOTO,
IF, INPUT, INT, LET, LIST, NEW, NEXT, PRINT,
READ, REM, RESTORE, RETURN, RND, RUN, SGN,
SIN, SQR, STEP, STOP, TAB, THEN, TO, USR
```

#### 8K BASIC Additional Keywords (future extension possibility):
```
ASC, AND, ATN, CHR$, CLOAD, CONT, COS, CSAVE,
DEF, EXP, FN, FRE, INP, LEFT$, LEN, LOG, MID$,
NULL, ON, OR, NOT, OUT, PEEK, POKE, POS, RIGHT$,
SPC, STR$, TAN, VAL, WAIT
```
