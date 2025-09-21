#include "parser.h"
#include "common.h"
#include <stdlib.h>
#include "memory.h"

typedef struct {
    const ParsedArg* args;
    int count;
    int pos;
} TokenStream;

static const ParsedArg* current(TokenStream* ts) {
    return (ts->pos < ts->count) ? &ts->args[ts->pos] : NULL;
}

static void next(TokenStream* ts) { ts->pos++; }

static ResultCode parseFactor(TokenStream* ts, float* outNum, char* outStr) {
    const ParsedArg* tok = current(ts);
    if (!tok) return RESULT_SYNTAX_ERROR;

    if (tok->type == ARG_TYPE_NUMBER) {
        if (outNum) *outNum = (float)mini_atoi(tok->value);
        next(ts);
        return RESULT_OK;
    } 
    
    if (tok->type == ARG_TYPE_VARIABLE) {
        float* var = getVariable(tok->value);
        if (!var) return RESULT_ERROR;
        if (outNum) *outNum = *var;
        next(ts);
        return RESULT_OK;
    } 
    
    if (tok->type == ARG_TYPE_STRING) {
        if (outStr) mini_strcpy(outStr, tok->value);
        next(ts);
        return RESULT_OK;
    }

    return RESULT_SYNTAX_ERROR;
}

static ResultCode parseTerm(TokenStream* ts, float* outNum) {
    float left;
    ResultCode rc = parseFactor(ts, &left, NULL);
    if (rc != RESULT_OK) return rc;

    while (1) {
        const ParsedArg* tok = current(ts);
        if (!tok || tok->type != ARG_TYPE_OPERATOR) break;
        char op = tok->value[0];
        if (op == '*' || op == '/') {
            next(ts);
            float right;
            rc = parseFactor(ts, &right, NULL);
            if (rc != RESULT_OK) return rc;
            if (op == '*') {
                left *= right;
            }
            else {
                if (right == 0.0f) return RESULT_ERROR;
                left /= right;
            }
        } 
        else {
            break;
        }
    }
    *outNum = left;
    return RESULT_OK;
}

static ResultCode parseExpr(TokenStream* ts, float* outNum) {
    float left;
    ResultCode rc = parseTerm(ts, &left);
    if (rc != RESULT_OK) return rc;

    while (1) {
        const ParsedArg* tok = current(ts);
        if (!tok || tok->type != ARG_TYPE_OPERATOR) break;
        if (mini_strcmp(tok->value, "+") == 0 || mini_strcmp(tok->value, "-") == 0) {
            char op = tok->value[0];
            next(ts);
            float right;
            rc = parseTerm(ts, &right);
            if (rc != RESULT_OK) return rc;
            if (op == '+') left += right;
            else left -= right;
        } 
        else {
            break;
        }
    }
    *outNum = left;
    return RESULT_OK;
}

static ResultCode parseComparison(TokenStream* ts, int* outBool) {
    for (int i = 0; i < ts->count; i++) {
        if (ts->args[i].type == ARG_TYPE_OPERATOR && mini_strcmp(ts->args[i].value, "=") == 0) {
            TokenStream left = { ts->args, i, 0 };
            TokenStream right = { ts->args + i + 1, ts->count - i - 1, 0 };
            float lval = 0, rval = 0;
            ResultCode rc1 = parseExpr(&left, &lval);
            ResultCode rc2 = parseExpr(&right, &rval);
            if (rc1 != RESULT_OK || rc2 != RESULT_OK) return RESULT_ERROR;
            if (outBool) *outBool = (lval == rval);
            return RESULT_OK;
        }
    }
    return RESULT_ERROR;
}

static ResultCode parseConcat(const ParsedArg* args, int count, char* outStr) {
    if (!outStr) return RESULT_ERROR;
    outStr[0] = '\0';
    for (int i = 0; i < count; i++) {
        if (args[i].type == ARG_TYPE_STRING || args[i].type == ARG_TYPE_NUMBER) {
            mini_strcat(outStr, args[i].value);
            continue;
        } 
        
        if (args[i].type == ARG_TYPE_VARIABLE) {
            float* var = getVariable(args[i].value);
            if (!var) return RESULT_ERROR;
            char buf[12];
            mini_itoa((int)(*var), buf);
            mini_strcat(outStr, buf);
        }
    }
    return RESULT_OK;
}

ResultCode evalExpression(const ParsedArg* args, int count, char* out_str, float* out_num, int* out_bool) {
    if (!args || count <= 0) return RESULT_SYNTAX_ERROR;

    if (args[0].type == ARG_TYPE_STRING) {
        return parseConcat(args, count, out_str);
    }

    for (int i = 0; i < count; i++) {
        if (args[i].type == ARG_TYPE_OPERATOR && mini_strcmp(args[i].value, "=") == 0) {
            TokenStream ts = { args, count, 0 };
            return parseComparison(&ts, out_bool);
        }
    }

    TokenStream ts = { args, count, 0 };
    return parseExpr(&ts, out_num);
}