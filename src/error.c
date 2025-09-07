#include "error.h"
#include <stdlib.h>  // for abs()

// Minimal mapping of ResultCode to strings
static const char errorMessages[] =
    "OK\0"
    "Program exited\0"
    "Unknown error\0"
    "Generic error\0"
    "Syntax error\0"
    "Memory exceeded\0"
    "String exceeded\0"
    "Line not found\0";

const char* resultCodeToString(ResultCode code) {
    int idx = abs(code);
    const char *p = errorMessages;
    while (idx-- && *p) {
        while (*p++) ;
    }
    return p;
}
