#ifndef BASIC_REPL_H
#define BASIC_REPL_H

#include "error.h"

/**
 * Initializes the BASIC program environment.
 * Allocates memory for program lines, variables, and internal structures.
 *
 * @return ResultCode
 *   RESULT_OK if initialization succeeded,
 *   negative ResultCode if an error occurred (e.g., memory allocation failure).
 */
ResultCode initREPL(void);

/**
 * Runs the main Read-Eval-Print Loop (REPL) for the BASIC interpreter.
 * Reads user input, parses it, evaluates commands or program lines, 
 * and prints results or error messages.
 *
 * @return ResultCode
 *   RESULT_OK if REPL exits normally,
 *   RESULT_PRG_STOPPED if the user stopped the program,
 *   negative ResultCode for runtime errors.
 */
ResultCode runREPL(void);

/**
 * Frees all resources allocated for the BASIC program.
 * Cleans up memory used for program lines, variables, and temporary buffers.
 *
 * @return ResultCode
 *   RESULT_OK if cleanup succeeded,
 *   negative ResultCode if an error occurred during resource release.
 */
ResultCode freeREPL(void);

#endif
