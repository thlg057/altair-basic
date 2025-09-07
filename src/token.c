#include <stddef.h>  // for size_t
#include "common.h"
#include "token.h"

short tokenize(const char *code, char *keyword, ParsedArg *args, int max_args) {
    if (!code || !keyword || !args || max_args <= 0) return RESULT_ERROR;

    // Skip leading spaces
    while (isSpace(*code)) code++;

    // ---- Read keyword ----
    int i = 0;
    while (*code && !isSpace(*code) && i < MAX_TOKEN_LEN - 1) {
        keyword[i++] = *code++;
    }
    keyword[i] = '\0';

    while (isSpace(*code)) code++;

    int arg_count = 0;
    while (*code && arg_count < max_args) {
        i = 0;

        // Skip multiple spaces
        if (isSpace(*code)) { code++; continue; }

        ParsedArg *arg = &args[arg_count];

        // ---- String literal ----
        if (*code == '"') {
            code++; // skip opening quote
            while (*code && *code != '"' && i < MAX_TOKEN_LEN - 1) {
                arg->value[i++] = *code++;
            }
            arg->value[i] = '\0';
            arg->type = ARG_TYPE_STRING;
            if (*code == '"') code++; // skip closing quote
            arg_count++;
            continue;
        }

        // ---- Operator ----
        if (*code == '+' || *code == '-' || *code == '*' || *code == '/' || *code == '=') {
            arg->value[0] = *code++;
            arg->value[1] = '\0';
            arg->type = ARG_TYPE_OPERATOR;
            arg_count++;
            continue;
        }

        // ---- Word / variable / number ----
        while (*code && !isSpace(*code) &&
               *code != '+' && *code != '-' && *code != '*' &&
               *code != '/' && *code != '=' && *code != '"' &&
               i < MAX_TOKEN_LEN - 1) {
            arg->value[i++] = *code++;
        }
        arg->value[i] = '\0';

        // Determine type
        arg->type = ARG_TYPE_VARIABLE; // default
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

