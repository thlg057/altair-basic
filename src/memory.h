#ifndef MEMORY_H
#define MEMORY_H

/**
 * Returns a pointer to the variable storage for the given BASIC variable name.
 * Variable names are typically "A".."Z" or "A0".."Z9".
 *
 * @param name Variable name (null-terminated string).
 * @return Pointer to the float value for the variable, or NULL if invalid.
 */
float* getVariable(const char *name);

/**
 * Resets all BASIC variables to 0.
 */
void resetAllVariables(void);

#endif
