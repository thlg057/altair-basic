#ifndef INTERPRETER_H
#define INTERPRETER_H

typedef short (*GetNextLineFunc)(unsigned short current_line);

void resetForStack(void);
/**
 * Interprets and executes a single BASIC command line (immediate mode).
 *
 * @param line Null-terminated BASIC command line.
 * @return RESULT_OK if successful,
 *         RESULT_PRG_STOPPED if program was stopped,
 *         or a negative ResultCode on error.
 */
short interpret(const char* line, unsigned short current_line, GetNextLineFunc getNextLine);

#endif
