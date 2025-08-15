#ifndef ERROR_H
#define ERROR_H

typedef enum {
    RESULT_OK = 0,
    RESULT_ERROR = -1,
    RESULT_MEMORY_CAPACITY_ERROR = -2,
    RESULT_STRING_CAPACITY_ERROR = -3,
    RESULT_PRG_STOPPED = -4
} ResultCode;

/**
 * Convert a ResultCode to a readable string.
 * Minimal version: all messages are short to reduce binary size.
 */
const char* resultCodeToString(ResultCode code);

#endif // ERROR_H
