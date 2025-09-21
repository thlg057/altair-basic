#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "error.h"

/**
 * Evaluates a BASIC expression from a list of tokens.
 * Supports arithmetic operations with operator precedence (+, -, *, /),
 * string concatenation, and equality comparison.
 *
 * Depending on the expression, the result can be a number, a string, or a boolean.
 *
 * @param args      Array of ParsedArg tokens representing the expression.
 * @param count     Number of tokens in the array.
 * @param out_str   Output buffer for string result (if applicable, or NULL).
 * @param out_num   Output pointer for numeric result (if applicable, or NULL).
 * @param out_bool  Output pointer for boolean result (if applicable, or NULL).
 * @return RESULT_OK on success, or a negative ResultCode on error.
 *
 * Usage examples:
 *   - To evaluate a numeric expression: set out_num, pass NULL for others.
 *   - To evaluate a string concatenation: set out_str, pass NULL for others.
 *   - To evaluate a boolean comparison: set out_bool, pass NULL for others.
 */
ResultCode evalExpression(const ParsedArg* args, int count, char* out_str, float* out_num, int* out_bool);

#endif