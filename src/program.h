#ifndef PROGRAM_H
#define PROGRAM_H

#include "error.h"

/**
 * Clears all stored BASIC program lines from memory.
 * Resets the program storage to an empty state.
 *
 * @return RESULT_OK if successful, or a negative ResultCode on error.
 */
ResultCode clearProgram(void);

/**
 * Adds or replaces a line in the BASIC program.
 * If the line number exists, it is replaced; otherwise, it is inserted in order.
 *
 * @param line The full line of BASIC code (including line number).
 * @return RESULT_OK if successful, or a negative ResultCode on error.
 */
ResultCode addLine(const char *line);

/**
 * Executes the currently loaded BASIC program from the first line.
 *
 * @return RESULT_OK if program ran successfully,
 *         RESULT_PRG_STOPPED if stopped by user,
 *         or a negative ResultCode on error.
 */
ResultCode runProgram(void);

/**
 * Lists all stored BASIC program lines to the console, in order.
 *
 * @return RESULT_OK if successful, or a negative ResultCode on error.
 */
ResultCode listProgram(void);

#endif
