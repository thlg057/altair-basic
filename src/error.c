#include "error.h"
#include <stdlib.h>  // for abs()

// Minimal mapping of ResultCode to strings
static const char* const errorMessages[] = {
    "OK",                   // index 0 -> RESULT_OK
    "Generic error",        // index 1 -> RESULT_ERROR (-1)
    "Memory exceeded",      // index 2 -> RESULT_MEMORY_CAPACITY_ERROR (-2)
    "String exceeded",      // index 3 -> RESULT_STRING_CAPACITY_ERROR (-3)
    "Program stopped"       // index 4 -> RESULT_PRG_STOPPED (-4)
};

const char* resultCodeToString(ResultCode code) {
    int idx;

    if (code <= 0) {
        idx = abs(code);
    } else {
        return "Unknown error code";
    }

    if (idx >= 0 && idx < (int)(sizeof(errorMessages)/sizeof(errorMessages[0])))
        return errorMessages[idx];
    else
        return "Unknown error code";
}
