#ifndef COMMON_H
#define COMMON_H

#include <stddef.h> // for size_t
#include <stdio.h>  // for putchar
#include "error.h"

typedef enum {
    FALSE = 0,
    TRUE = 1
} Boolean;

static inline int isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static inline int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

static inline int isSpace(char c) {
    return c == ' ' || c == '\t';
}

static inline char toUpper(char c) {
    if (c >= 'a' && c <= 'z') return c - 32;
    return c;
}

static inline char toLower(char c) {
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

// Minimal case-insensitive string compare
static inline int strCaseCmp(const char* a, const char* b) {
    while (*a && *b) {
        char ca = (*a >= 'a' && *a <= 'z') ? *a - 32 : *a;
        char cb = (*b >= 'a' && *b <= 'z') ? *b - 32 : *b;
        if (ca != cb) {
          return ca - cb;
        }

        a++; b++;
    }

    return *a - *b;
}

static inline short strCheckMaxSize(const char *s, unsigned char limit) {
    unsigned char len = 0;
    while (*s) {
        if (++len > limit) return RESULT_ERROR;
        s++;
    }

    return RESULT_OK;
}

static inline void strCopyTruncate(char *dest, const char *src, size_t max_len) {
    size_t i = 0;
    while (i < max_len && src[i]) {
        dest[i] = src[i];
        i++;
    }

    dest[i < max_len ? i : max_len - 1] = '\0'; // always terminate properly
}

static inline void printStr(const char* s, Boolean newline) {
    while (*s)  putchar(*s++);
    if (newline) putchar('\n');
}

static inline void printUnsigned(unsigned short n, Boolean newline) {
    char buf[6]; // max 65535 + '\0'
    int i = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    while (n > 0 && i < 5) {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }

    // Affiche en ordre inverse
    while (i > 0) putchar(buf[--i]);
    if (newline) putchar('\n');
}

#define print(x, newline) _Generic((x), \
    const char*: printStr, \
    char*: printStr, \
    unsigned short: printUnsigned \
)(x, newline)

#endif
