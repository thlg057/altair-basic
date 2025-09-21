#include <stdio.h>
#include "program.h"
#include "error.h"
#include "test_utilities.h"

int test_init_and_freeProgram(void) {
    ResultCode res;

    res = initProgram();
    ASSERT(res == RESULT_OK, "initProgram should return RESULT_OK");

    res = freeProgram();
    ASSERT(res == RESULT_OK, "freeProgram should return RESULT_OK");

    return TEST_OK;
}
