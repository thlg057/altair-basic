# Windows C Development Setup with MSYS2

This guide explains how to set up a development environment on Windows to compile and run a minimal BASIC interpreter project using MSYS2.

---

## 1. Install MSYS2

1. Download the installer from [https://www.msys2.org](https://www.msys2.org).
2. Run the installer and follow the default instructions.
3. Launch the MSYS2 terminal (`MSYS2 MinGW 64-bit`) after installation.
4. Update the package database and core system packages:

```bash
pacman -Syu
```

> Note: If the terminal closes after update, reopen it and run the command again.

---

## 2. Install Development Tools

Install GCC, make, and basic utilities:

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

- `base-devel` includes `make`, `patch`, `tar`, etc.
- `mingw-w64-x86_64-toolchain` provides GCC, G++, GDB, and other compilers for 64-bit Windows.

---

## 3. Set Up Environment in VS Code

1. Install [Visual Studio Code](https://code.visualstudio.com/).
2. Install the **C/C++ extension** from Microsoft.
3. Configure VS Code to use the MSYS2 MinGW 64-bit terminal:
   - Open `settings.json` (Ctrl+, → search `terminal.integrated.profiles.windows`) and add:

```json
"terminal.integrated.profiles.windows": {
    "MSYS2": {
        "path": "C:\\msys64\\usr\\bin\\bash.exe",
        "args": ["--login", "-i"]
    }
},
"terminal.integrated.defaultProfile.windows": "MSYS2"
```

4. Open a new terminal in VS Code to use MSYS2.

---

## 4. Project Dependencies

No external libraries are needed for this minimal BASIC interpreter project. Standard C libraries (stdio.h, string.h, ctype.h, stdlib.h) are sufficient.

---

## 5. Building the Project

1. Navigate to the project folder in the MSYS2 terminal:

```bash
cd /c/Users/<username>/projects/minimal_basic
```

2. Run `make` to build the project:

```bash
make
```

- This will compile the source files and produce `bin/basic.exe`.

3. To build a debug version with symbols:

```bash
make debug
```

---

## 6. Running Tests

If you have unit tests (for example in `tests/`):

```bash
make test
```

- This will compile and run the test executables.

---

## 7. Notes on Optimizations

- Your `Makefile` includes flags like:

```text
-Os -s -ffunction-sections -fdata-sections -Wl,--gc-sections
```

These options reduce binary size by optimizing for size and removing unused sections.

- Use `strip` to remove debug symbols from the final binary:

```bash
strip bin/basic.exe
```

---

## 8. References

- [MSYS2 Installation Guide](https://www.msys2.org)
- [GCC for Windows (MinGW-w64)](https://www.mingw-w64.org/)
- [Visual Studio Code C/C++ Setup](https://code.visualstudio.com/docs/languages/cpp)

