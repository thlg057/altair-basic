#include <stddef.h>
#include "common.h"
#include "token.h"

static inline Boolean isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '=';
}

short tokenize(const char *code, char *keyword, ParsedArg *args, int maxArgs) {
    if (!code || !keyword || !args || maxArgs <= 0) return RESULT_ERROR;

    while (isSpace(*code)) code++;

    int i = 0;
    while (*code && !isSpace(*code) && i < MAX_TOKEN_LEN - 1) {
        keyword[i++] = *code++;
    }
    keyword[i] = '\0';

    while (isSpace(*code)) code++;

    int argCount = 0;
    while (*code && argCount < maxArgs) {
        i = 0;

        if (isSpace(*code)) { code++; continue; }

        ParsedArg *arg = &args[argCount];

        if (*code == '"') {
            code++; // skip opening quote
            while (*code && *code != '"' && i < MAX_TOKEN_LEN - 1) {
                arg->value[i++] = *code++;
            }
            arg->value[i] = '\0';
            arg->type = ARG_TYPE_STRING;
            if (*code == '"') code++;
            argCount++;
            continue;
        }

        if (isDigit(*code) || (*code == '-' && isDigit(*(code + 1)))) {
            if (*code == '-') {
                arg->value[i++] = *code++;
            }
            while (*code && isDigit(*code) && i < MAX_TOKEN_LEN - 1) {
                arg->value[i++] = *code++;
            }
            arg->value[i] = '\0';
            arg->type = ARG_TYPE_NUMBER;
            argCount++;
            continue;
        }

        if (isOperator(*code)) {
            arg->value[0] = *code++;
            arg->value[1] = '\0';
            arg->type = ARG_TYPE_OPERATOR;
            argCount++;
            continue;
        }

        while (*code && !isSpace(*code) &&
               *code != '+' && *code != '-' && *code != '*' &&
               *code != '/' && *code != '=' && *code != '"' &&
               i < MAX_TOKEN_LEN - 1) {
            arg->value[i++] = *code++;
        }
        arg->value[i] = '\0';

        arg->type = ARG_TYPE_VARIABLE; 
        argCount++;
    }

    return argCount;
}

