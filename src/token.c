#include <stddef.h>
#include "common.h"
#include "token.h"

static inline Boolean isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '=';
}

short tokenize(const char *code, char *keyword, ParsedArg *args, int max_args) {
    if (!code || !keyword || !args || max_args <= 0) return RESULT_ERROR;

    while (isSpace(*code)) code++;

    int i = 0;
    while (*code && !isSpace(*code) && i < MAX_TOKEN_LEN - 1) {
        keyword[i++] = *code++;
    }
    keyword[i] = '\0';

    while (isSpace(*code)) code++;

    int arg_count = 0;
    while (*code && arg_count < max_args) {
        i = 0;

        if (isSpace(*code)) { code++; continue; }

        ParsedArg *arg = &args[arg_count];

        if (*code == '"') {
            code++; // skip opening quote
            while (*code && *code != '"' && i < MAX_TOKEN_LEN - 1) {
                arg->value[i++] = *code++;
            }
            arg->value[i] = '\0';
            arg->type = ARG_TYPE_STRING;
            if (*code == '"') code++;
            arg_count++;
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
            arg_count++;
            continue;
        }

        if (isOperator(*code)) {
            arg->value[0] = *code++;
            arg->value[1] = '\0';
            arg->type = ARG_TYPE_OPERATOR;
            arg_count++;
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
        int is_num = 1;
        for (int k = 0; arg->value[k]; k++) {
            if (!isDigit(arg->value[k])) {
                is_num = 0;
                break;
            }
        }
        if (is_num) arg->type = ARG_TYPE_NUMBER;

        arg_count++;
    }

    return arg_count;
}

