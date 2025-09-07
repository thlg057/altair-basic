#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <stdio.h>
#include <string.h>

// ---- Assertion macros ----

// Assert generic condition
#define ASSERT(cond, msg) do { \
    if (!(cond)) { \
        printf("[FAIL] %s (at %s:%d)\n", msg, __FILE__, __LINE__); \
        return -1; \
    } \
} while(0)

// Assert string equality
#define ASSERT_STR_EQ(actual, expected, msg) do { \
    if (strcmp((actual), (expected)) != 0) { \
        printf("[FAIL] %s (expected: \"%s\", got: \"%s\") at %s:%d\n", \
               msg, expected, actual, __FILE__, __LINE__); \
        return -1; \
    } \
} while(0)

// Assert integer equality
#define ASSERT_INT_EQ(actual, expected, msg) do { \
    if ((actual) != (expected)) { \
        printf("[FAIL] %s (expected: %d, got: %d) at %s:%d\n", \
               msg, expected, actual, __FILE__, __LINE__); \
        return -1; \
    } \
} while(0)

// ---- Stream restore functions ----
void restoreStdin(void);
void restoreStdout(void);

#endif // TEST_COMMON_H
