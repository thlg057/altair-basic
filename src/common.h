#ifndef COMMON_H
#define COMMON_H

#include <stddef.h> // for size_t
#include <stdio.h>  // for putchar

// Minimal case-insensitive string compare
static inline int myStrCaseCmp(const char* a, const char* b) {
    while (*a && *b) {
        char ca = (*a >= 'a' && *a <= 'z') ? *a - 32 : *a;
        char cb = (*b >= 'a' && *b <= 'z') ? *b - 32 : *b;
        if (ca != cb) return ca - cb;
        a++; b++;
    }
    return *a - *b;
}

// Minimal print line function
static inline void printLine(const char* s) {
    while (*s) putchar(*s++);
    putchar('\n');
}

#endif // COMMON_H
