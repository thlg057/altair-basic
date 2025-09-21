#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKEN_LEN 32

/**
 * Argument types for parsed BASIC tokens.
 */
typedef enum {
    ARG_TYPE_VARIABLE,  ///< Variable name (e.g., A, X1)
    ARG_TYPE_STRING,    ///< String literal (e.g., "HELLO")
    ARG_TYPE_NUMBER,    ///< Numeric literal (e.g., 42)
    ARG_TYPE_OPERATOR   ///< Operator (e.g., =, +, -)
} ArgType;

/**
 * Structure representing a parsed argument (token) from a BASIC line.
 */
typedef struct {
    ArgType type;               ///< Type of argument
    char value[MAX_TOKEN_LEN];  ///< Value as string (null-terminated)
} ParsedArg;

/**
 * Tokenizes a BASIC code line into a keyword and argument list.
 *
 * @param code      Input BASIC line (null-terminated).
 * @param keyword   Output buffer for the command keyword.
 * @param args      Output array of ParsedArg for arguments.
 * @param max_args  Maximum number of arguments to parse.
 * @return Number of arguments parsed, or negative ResultCode on error.
 */
short tokenize(const char *code, char *keyword, ParsedArg *args, int max_args);

#endif

