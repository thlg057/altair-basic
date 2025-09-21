#ifndef ERROR_H
#define ERROR_H

/**
 * Result codes for all BASIC interpreter functions.
 * All functions must return RESULT_OK (0) on success, or a negative ResultCode on error.
 */
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
 * Converts a ResultCode to a short, human-readable string.
 * Used for error reporting and debugging.
 *
 * @param code The ResultCode to convert.
 * @return Pointer to a static string describing the code.
 */
const char* resultCodeToString(ResultCode code);

#endif // ERROR_H
