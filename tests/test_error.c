#include <stdio.h>
#include "error.h"
#include "test_utilities.h"

int test_errorModule(void) {
    ASSERT(resultCodeToString(RESULT_OK) != NULL, "RESULT_OK should return a message");
    ASSERT(resultCodeToString(RESULT_ERROR) != NULL, "RESULT_ERROR should return a message");
    ASSERT(resultCodeToString(RESULT_MEMORY_CAPACITY_ERROR) != NULL, "RESULT_MEMORY_CAPACITY_ERROR should return a message");
    ASSERT(resultCodeToString(RESULT_STRING_CAPACITY_ERROR) != NULL, "RESULT_STRING_CAPACITY_ERROR should return a message");
    ASSERT(resultCodeToString(RESULT_PRG_STOPPED) != NULL, "RESULT_PRG_STOPPED should return a message");
    ASSERT(resultCodeToString(9999) != NULL, "Unknown code should return a message");
    return 0;
}
