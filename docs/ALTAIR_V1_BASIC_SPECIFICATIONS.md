# Altair BASIC (4K) Specifications — Version 1

## Overview

This document summarizes the original specifications of the Altair BASIC 4K interpreter developed by Bill Gates, Paul Allen, and Monte Davidoff in **1975** for the MITS Altair 8800. It is based on the **Altair 4K BASIC Reference Manual**.

Reference: MITS Altair BASIC Reference Manual (1975) :contentReference[oaicite:0]{index=0}

---

## General Characteristics

- **Interpreter Size**: Approximately **4 KB** of memory (interpreter + runtime)  
- **Available Memory**: Around **700–900 bytes** left for user programs :contentReference[oaicite:1]{index=1}  
- **Memory Constraints**: Forced compact data structures; lines are **tokenized** instead of stored as text :contentReference[oaicite:2]{index=2}

---

## Language Features

### Variables

- Only **numeric variables** supported (no strings)  
- **Variable names** limited to **one or two characters** (e.g., `A`, `X1`) :contentReference[oaicite:3]{index=3}  

### Statements & Keywords

The following are supported commands and statements in Altair BASIC 4K:

- **Program Control**
  - `NEW` — clear the program memory  
  - `RUN` — execute the loaded program  
  - `LIST` — display the stored program lines  
  - `STOP` / `END` — terminate execution  
- **Flow Control**
  - `GOTO` — unconditional jump to a line number  
  - `FOR` / `NEXT` — loop constructs  
  - `IF <expr> THEN <line>` — simple conditional branching (one relational operator only) :contentReference[oaicite:4]{index=4}  
- **Input / Output**
  - `PRINT <expression>` — display numeric expressions  
  - `INPUT <variable>` — get a numeric input from the user (some versions)  
- **Mathematical Functions**
  - Basic arithmetic: `+`, `-`, `*`, `/`  
  - `ABS`, `INT`, and limited floating-point arithmetic capabilities :contentReference[oaicite:5]{index=5}

---

## Limitations

- **No strings** (string variables or manipulation functions) in 4K version. That was introduced in later 8K versions. :contentReference[oaicite:6]{index=6}  
- **Limited built-in functions** (no trig, no random `RND`, no Boolean operators in 4K) :contentReference[oaicite:7]{index=7}  
- **Single relational operator** per `IF` statement only (e.g., `IF A < B THEN`) :contentReference[oaicite:8]{index=8}  

---

## Summary Table

| Feature        | Description                                         |
|----------------|-----------------------------------------------------|
| Built-in Size  | ~4 KB interpreter size                              |
| Storage Model  | Tokenized lines in memory                           |
| Variables      | Numeric only, 1–2 characters                        |
| Control Flow   | `GOTO`, `FOR/NEXT`, `IF...THEN`     |
| I/O            | `PRINT`, `INPUT`                           |
| Functions      | Arithmetic ops, `ABS`, `INT`, floating-point       |
| Limitations    | No strings, no advanced functions, single IF test  |

---

## Reference

- MITS Altair BASIC Reference Manual, 4K BASIC edition, 1975. :contentReference[oaicite:9]{index=9}

---

*This document is generated to provide a concise technical overview of the language as implemented in the original Altair BASIC interpreter, preserving the design constraints and feature set of the era.*
