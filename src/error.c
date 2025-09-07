#include "error.h"
#include <stdlib.h>  // for abs()

// Minimal mapping of ResultCode to strings
static const char* const errorMessages[] = {
    "OK",                   // index 0 -> RESULT_OK
    "Program exited",       // RESULT_PRG_STOPPED
    "Unkonwn error",        // RESULT_UNKNOW_ERROR
    "Generic error",        // RESULT_ERROR
    "Syntax error",         // RESULT_SYNTAX_ERROR
    "Memory exceeded",      // RESULT_MEMORY_CAPACITY_ERROR
    "String exceeded"       // RESULT_STRING_CAPACITY_ERROR 
};

const char* resultCodeToString(ResultCode code) {
    int idx = RESULT_UNKNOW_ERROR;

    if (code <= 0) {
        idx = abs(code);
        if (idx >= (int)(sizeof(errorMessages)/sizeof(errorMessages[0]))) {
            idx = RESULT_UNKNOW_ERROR;
        }
    } 

    return errorMessages[idx];
}
