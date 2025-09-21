#ifndef INTERPRETER_H
#define INTERPRETER_H

/**
 * Function pointer type for getting the next line number in a BASIC program.
 * Used by FOR/NEXT loops to implement proper control flow.
 * @param current_line Current line number
 * @return Next line number, or negative ResultCode on error
 */
typedef short (*GetNextLineFunc)(unsigned short current_line);

/**
 * Resets the FOR loop stack.
 * Should be called when starting a new program or clearing variables.
 */
void resetForStack(void);

/**
 * Interprets and executes a single BASIC command line.
 * Supports all BASIC commands: PRINT, LET, GOTO, IF, INPUT, FOR, NEXT, etc.
 *
 * @param line Null-terminated BASIC command line
 * @param current_line Current line number (for control flow)
 * @param getNextLine Function to get next line number
 * @return RESULT_OK if successful,
 *         Positive line number for GOTO operations,
 *         RESULT_PRG_STOPPED if program was stopped,
 *         or negative ResultCode on error
 */
short interpret(const char* line, unsigned short current_line, GetNextLineFunc getNextLine);

#endif
