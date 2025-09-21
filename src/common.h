#ifndef COMMON_H
#define COMMON_H

#include <stddef.h> // for size_t
#include <stdio.h>  // for putchar
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#endif
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

/**
 * Minimal string copy (null-terminated).
 * Returns dest.
 */
static inline char* mini_strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++));
    return dest;
}

/**
 * Minimal string concatenation (null-terminated).
 * Returns dest.
 */
static inline char* mini_strcat(char* dest, const char* src) {
    char* d = dest;
    while (*d) d++;
    while ((*d++ = *src++));
    return dest;
}

/**
 * Minimal string compare (case-sensitive).
 * Returns 0 if equal, <0 if s1<s2, >0 if s1>s2.
 */
static inline int mini_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

/**
 * Minimal ASCII to integer conversion (no float support).
 */
static inline int mini_atoi(const char* s) {
    int r = 0, sign = 1;
    if (*s == '-') { sign = -1; s++; }
    while (*s >= '0' && *s <= '9') {
        r = r * 10 + (*s - '0');
        s++;
    }
    return r * sign;
}

/**
 * Minimal integer to string conversion (base 10).
 * Returns dest.
 */
static inline char* mini_itoa(int n, char* dest) {
    char buf[12];
    int i = 0, sign = n < 0;
    if (sign) n = -n;
    do { buf[i++] = '0' + (n % 10); n /= 10; } while (n);
    if (sign) buf[i++] = '-';
    int j = 0;
    while (i--) dest[j++] = buf[i];
    dest[j] = 0;
    return dest;
}

/**
 * Minimal ASCII to float conversion.
 * Handles optional sign, integer and fractional part (no exponent, no locale).
 */
static inline float mini_atof(const char* s) {
    float result = 0.0f, factor = 1.0f;
    int sign = 1;

    // Skip leading spaces
    while (*s == ' ' || *s == '\t') s++;

    // Handle sign
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') { s++; }

    // Integer part
    while (*s >= '0' && *s <= '9') {
        result = result * 10.0f + (*s - '0');
        s++;
    }

    // Fractional part
    if (*s == '.') {
        s++;
        float frac = 0.0f, base = 0.1f;
        while (*s >= '0' && *s <= '9') {
            frac += (*s - '0') * base;
            base *= 0.1f;
            s++;
        }
        result += frac;
    }

    return sign * result;
}

#endif
