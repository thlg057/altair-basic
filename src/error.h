#ifndef ERROR_H
#define ERROR_H

typedef enum {
    RESULT_OK = 0,
    RESULT_PRG_STOPPED = -1,
    RESULT_UNKNOW_ERROR = -2,
    RESULT_ERROR = -3,
    RESULT_SYNTAX_ERROR = -4,
    RESULT_MEMORY_CAPACITY_ERROR = -5,
    RESULT_STRING_CAPACITY_ERROR = -6,
    RESULT_LINE_NOT_FOUND_ERROR = -7
} ResultCode;

/**
 * Convert a ResultCode to a readable string.
 * Minimal version: all messages are short to reduce binary size.
 */
const char* resultCodeToString(ResultCode code);

#endif // ERROR_H
