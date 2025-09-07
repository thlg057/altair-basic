#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKEN_LEN 64

typedef enum {
    ARG_TYPE_VARIABLE,
    ARG_TYPE_STRING,
    ARG_TYPE_NUMBER,
    ARG_TYPE_OPERATOR
} ArgType;

typedef struct {
    ArgType type;
    char value[MAX_TOKEN_LEN];
} ParsedArg;

short tokenize(const char *code, char *keyword, ParsedArg *args, int max_args);
#endif

