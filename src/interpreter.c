#include <stddef.h>   // for size_t, pointer arithmetic
#include "common.h"   
#include "memory.h"
#include "error.h"
#include "token.h"
#include "interpreter.h"

#define MAX_ARGS 10

short defaultImplementation(const char* cmd, ParsedArg args[], short count) {
    print("executing ", FALSE);
    print(cmd, FALSE);
    print("with ", FALSE);
    for (int i = 0; i < count; i++) {
        print(args[i].value, FALSE);
        print(" ", FALSE);
    }

    print("", TRUE);
    return RESULT_OK;
}

short doPrint(ParsedArg args[], short count) {
    print(args[0].value, TRUE);
    return RESULT_OK;
}

short doGoto(ParsedArg args[], short count) {
    int val = 0;

    if (!args[0].value || *args[0].value == '\0') return RESULT_ERROR; 

    for (const char *p = args[0].value; *p != '\0'; p++) {
        if (*p < '0' || *p > '9')  return RESULT_ERROR; 
        val = val * 10 + (*p - '0');
    }

    return (short)val;
}

short doLet(ParsedArg args[], short count) {
    return defaultImplementation("LET", args, count);
}

short doIf(ParsedArg args[], short count) {
    return defaultImplementation("IF", args, count);
}

short doFor(ParsedArg args[], short count) {
    return defaultImplementation("FOR", args, count);
}

short doInput(ParsedArg args[], short count) {
    return defaultImplementation("INPUT", args, count);
}

short interpret(const char* line) {
char keyword[10];
    ParsedArg args[MAX_ARGS];
    short count = tokenize(line, keyword, args, MAX_ARGS);
    if (strCaseCmp(keyword, "END") == 0 || strCaseCmp(keyword, "STOP") == 0) {
        return RESULT_PRG_STOPPED;
    }

    if (strCaseCmp(keyword, "PRINT") == 0) {
        return doPrint(args, count);
    }

    if (strCaseCmp(keyword, "GOTO") == 0) {
        return doGoto(args, count);
    }
    
    return RESULT_ERROR;
}
