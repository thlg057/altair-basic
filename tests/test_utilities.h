#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

#include <stdio.h>
#include <string.h>

typedef enum {
    TEST_OK = 0,
    TEST_ERROR = -1
} TestCode;

#if defined(_WIN32) || defined(_WIN64)
    #include <io.h>
    #define FILENO _fileno
    #define DUP _dup
    #define DUP2 _dup2
    #define CLOSE _close
#else
    #include <unistd.h>
    #define FILENO fileno
    #define DUP dup
    #define DUP2 dup2
    #define CLOSE close
#endif

// Redirects stdout to a file, returns the saved file descriptor
static inline int redirectStdoutToFile(FILE* f) {
    fflush(stdout);
    int fd = FILENO(stdout);
    int saved_fd = DUP(fd);
    DUP2(FILENO(f), fd);
    return saved_fd;
}

// Restores stdout from the saved file descriptor
static inline void restoreStdoutFd(int saved_fd) {
    if (saved_fd < 0) return;
    int fd = FILENO(stdout);
    DUP2(saved_fd, fd);
    CLOSE(saved_fd);
}

// Reads the content of a file into a buffer (null-terminated)
static inline int readFileToBuffer(const char* filename, char* buffer, int bufsize) {
    FILE* f = fopen(filename, "r");
    if (!f) return 1;
    size_t n = fread(buffer, 1, bufsize - 1, f);
    buffer[n] = 0;
    fclose(f);
    return 0;
}

// Removes the first newline character found in the buffer
static inline void removeNewline(char* buffer) {
    char* p = strpbrk(buffer, "\r\n");
    if (p) *p = 0;
}

// ---- Assertion macros ----

// Assert generic condition
#define ASSERT(cond, msg) do { \
    if (!(cond)) { \
        printf("[FAIL] %s (at %s:%d)\n", msg, __FILE__, __LINE__); \
        return TEST_ERROR; \
    } \
} while(0)

// Assert string equality
#define ASSERT_STR_EQ(actual, expected, msg) do { \
    if (strcmp((actual), (expected)) != 0) { \
        printf("[FAIL] %s (expected: \"%s\", got: \"%s\") at %s:%d\n", \
               msg, expected, actual, __FILE__, __LINE__); \
        return TEST_ERROR; \
    } \
} while(0)

// Assert integer equality
#define ASSERT_INT_EQ(actual, expected, msg) do { \
    if ((actual) != (expected)) { \
        printf("[FAIL] %s (expected: %d, got: %d) at %s:%d\n", \
               msg, expected, actual, __FILE__, __LINE__); \
        return TEST_ERROR; \
    } \
} while(0)

// ---- Stream restore functions ----
void restoreStdin(void);
void restoreStdout(void);

#endif // TEST_COMMON_H
