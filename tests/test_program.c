#include <stdio.h>
#include "program.h"
#include "error.h"

#define ASSERT(cond, msg) do { \
    if (!(cond)) { \
        printf("Test failed: %s\n", msg); \
        return -1; \
    } \
} while(0)

int test_init_and_freeProgram(void) {
    ResultCode res;

    res = initProgram();
    ASSERT(res == RESULT_OK, "initProgram should return RESULT_OK");

    res = freeProgram();
    ASSERT(res == RESULT_OK, "freeProgram should return RESULT_OK");

    return 0;
}
