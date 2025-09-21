#include <stddef.h>   // for size_t, pointer arithmetic
#include "common.h"   
#include "memory.h"
#include "error.h"
#include "token.h"
#include "interpreter.h"
#include "parser.h"

#define MAX_ARGS 8       
#define MAX_FOR_STACK 3  

typedef struct {
    char var_name[3];
    float end_value;
    float step;
    unsigned short for_line;
} ForStackEntry;

static ForStackEntry for_stack[MAX_FOR_STACK];
static int forStackTop = 0;

void resetForStack(void) {
    forStackTop = 0;
}

short doPrint(ParsedArg args[], short count) {
    char strResult[128] = {0};
    float numResult = 0;
    ResultCode rc;

    rc = evalExpression(args, count, strResult, &numResult, NULL);
    if (rc != RESULT_OK) {
        return rc;
    }

    if (strResult[0]) {
        print(strResult, TRUE);
        return RESULT_OK;
    }

    char buf[32];
    mini_itoa((int)numResult, buf);
    print(buf, TRUE);
    return RESULT_OK;
}

short doGoto(ParsedArg args[], short count) {
    if (count != 1) return RESULT_ERROR;
    int val = 0;

    if (!args[0].value || *args[0].value == '\0') return RESULT_ERROR; 

    for (const char *p = args[0].value; *p != '\0'; p++) {
        if (!isDigit(*p))  return RESULT_ERROR; 
        val = val * 10 + (*p - '0');
    }

    return (short)val;
}

short doLet(ParsedArg args[], short count) {
    if (count < 3) return RESULT_ERROR;
    if (!args[0].value || *args[0].value == '\0' || args[0].type != ARG_TYPE_VARIABLE) return RESULT_ERROR; 
    if (args[1].type != ARG_TYPE_OPERATOR || args[1].value[0] != '=') return RESULT_ERROR;
    
    float numResult = 0;
    ResultCode rc;
    rc = evalExpression(args + 2, count - 2, NULL, &numResult, NULL);
    if (rc != RESULT_OK) {
        return rc;
    }

    *getVariable(args[0].value) = numResult;
    return RESULT_OK;
}

short doIf(ParsedArg args[], short count) {
    if (count < 3) return RESULT_ERROR;
    int condEnd = count - 2;
    if (mini_strcmp(args[condEnd].value, "GOTO") != 0 ) return RESULT_ERROR;

    int condResult = 0;
    ResultCode rc = evalExpression(args, condEnd, NULL, NULL, &condResult);
    if (rc != RESULT_OK) return rc;

    if (condResult) {
        return doGoto(&args[count-1], 1);
    }

    return RESULT_OK;
}

short doInput(ParsedArg args[], short count) {
    if (count != 1 || args[0].type != ARG_TYPE_VARIABLE) return RESULT_ERROR;

    char line[32];
    print(args[0].value, FALSE);
    print("? ", FALSE);
    if (!fgets(line, sizeof(line), stdin)) return RESULT_ERROR;

    float value = mini_atof(line);

    float* var = getVariable(args[0].value);
    if (!var) return RESULT_ERROR;

    *var = value;
    return RESULT_OK;
}

short doFor(ParsedArg args[], short count, unsigned short current_line, GetNextLineFunc getNextLine) {
    if (count < 5) return RESULT_SYNTAX_ERROR;
    if (forStackTop >= MAX_FOR_STACK) return RESULT_MEMORY_CAPACITY_ERROR;

    if (args[1].type != ARG_TYPE_OPERATOR || args[1].value[0] != '=') return RESULT_SYNTAX_ERROR;

    if (strCaseCmp(args[3].value, "TO") != 0) return RESULT_SYNTAX_ERROR;

    float step = 1.0f;
    if (count >= 6) {
        if (count < 7) return RESULT_SYNTAX_ERROR;
        if (strCaseCmp(args[5].value, "STEP") != 0) return RESULT_SYNTAX_ERROR;
        step = mini_atof(args[6].value);
        if (step == 0.0f) return RESULT_SYNTAX_ERROR;
    }

    short nextLine = getNextLine(current_line);
    if (nextLine < 0) {
        return nextLine;
    }

    float start = mini_atof(args[2].value);
    float end = mini_atof(args[4].value);

    float* var = getVariable(args[0].value);
    if (!var) return RESULT_ERROR;
    *var = start;

    mini_strcpy(for_stack[forStackTop].var_name, args[0].value);
    for_stack[forStackTop].end_value = end;
    for_stack[forStackTop].step = step;
    for_stack[forStackTop].for_line = (unsigned short)nextLine;
    forStackTop++;

    return RESULT_OK;
}

short doNext(ParsedArg args[], short count) {
    if (forStackTop <= 0) return RESULT_ERROR;

    ForStackEntry* entry = &for_stack[forStackTop - 1];
    if (mini_strcmp(entry->var_name, args[0].value) != 0) return RESULT_ERROR;

    float* var = getVariable(entry->var_name);
    if (!var) return RESULT_ERROR;
    *var += entry->step;

    int finished = (entry->step > 0) ? (*var > entry->end_value) : (*var < entry->end_value);
    if (finished) {
        forStackTop--;
        return RESULT_OK;
    } 

    return (short)entry->for_line;
}

short interpret(const char* line, unsigned short current_line, GetNextLineFunc getNextLine) {
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

    if (strCaseCmp(keyword, "LET") == 0) {
        return doLet(args, count);
    }
    
    if (strCaseCmp(keyword, "IF") == 0) {
        return doIf(args, count);
    }

    if (strCaseCmp(keyword, "INPUT") == 0) {
        return doInput(args, count);
    }

    if (strCaseCmp(keyword, "FOR") == 0) {
        return doFor(args, count, current_line, getNextLine);
    }

    if (strCaseCmp(keyword, "NEXT") == 0) {
        return doNext(args, count);
    }

    return RESULT_ERROR;
}
