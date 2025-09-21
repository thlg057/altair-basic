#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "program.h"
#include "error.h"
#include "common.h"
#include "interpreter.h"
#include "memory.h"

// Maximum number of BASIC program lines that can be stored
#define MAX_LINES 50
// Maximum length of a command line (excluding line number)
#define MAX_CMDLINE_SIZE 72
// Maximum total length of an input line (including line number)
#define MAX_LINE_SIZE 80
// Maximum value for unsigned short (65535)
#define MAX_UNSIGNED_INT 65535

typedef struct {
    unsigned short line_number;
    char text[MAX_CMDLINE_SIZE + 1];
} BasicLine;

typedef struct {
    BasicLine lines[MAX_LINES];
    unsigned char count;
} BasicProgram;

static BasicProgram program;

short parseLine(const char *input, unsigned short *lineNumber, char *code, size_t codeSize) {
    if (!input || !lineNumber || !code) {
        return RESULT_ERROR;
    }

    while (*input == ' ' || *input == '\t') {
        input++;
    }

    unsigned int num = 0;
    if (*input < '0' || *input > '9') {
        return RESULT_SYNTAX_ERROR;
    }

    while (*input >= '0' && *input <= '9') {
        num = num * 10 + (*input - '0');
        if (num > MAX_UNSIGNED_INT) {
            return RESULT_SYNTAX_ERROR;
        } 

        input++;
    }

    *lineNumber = (unsigned short)num;
    while (*input == ' ' || *input == '\t') {
        input++;
    }

    size_t i = 0;
    while (i < codeSize - 1 && input[i] != '\0') {
        code[i] = input[i];
        i++;
    }

    code[i] = '\0';
    return RESULT_OK;
}

static short findIndex(unsigned short targetLine) {
    for (unsigned char j = 0; j < program.count; j++) {
        if (program.lines[j].line_number == targetLine) {
            return j; 
        }
    }
    
    return RESULT_LINE_NOT_FOUND_ERROR;
}

static void sortProgram(void) {
    for (unsigned char i = 1; i < program.count; i++) {
        unsigned short key_num = program.lines[i].line_number;
        char key_text[MAX_CMDLINE_SIZE + 1];
        strcpy(key_text, program.lines[i].text);
        
        char j = i - 1;
        while (j >= 0 && program.lines[j].line_number > key_num) {
            program.lines[j + 1] = program.lines[j];
            j--;
        }
        
        program.lines[j + 1].line_number = key_num;
        strcpy(program.lines[j + 1].text, key_text);
    }
}

ResultCode clearProgram(void) {
    program.count = 0;
    resetAllVariables();
    resetForStack();
    return RESULT_OK;
}

ResultCode addLine(const char *line) {
    if (program.count >= MAX_LINES) {
        return RESULT_MEMORY_CAPACITY_ERROR;
    }

    if (strCheckMaxSize(line, MAX_LINE_SIZE) != RESULT_OK) {
        return RESULT_STRING_CAPACITY_ERROR;
    }

    ResultCode res;
    unsigned short lineNumber;
    char code[73];
    res = parseLine(line, &lineNumber, code, sizeof(code));
    if (res != RESULT_OK) {
        return res;
    }

    short index = findIndex(lineNumber);
    if (index < 0) {
        index = program.count;
        program.count++;
    }

    program.lines[index].line_number = lineNumber;
    strCopyTruncate(program.lines[index].text, code, MAX_CMDLINE_SIZE);
    return RESULT_OK;
}

short getNextLineNumber(unsigned short current_line) {
    short index = findIndex(current_line);
    if (index < 0) {
        return index;
    }

    index++;
    if (index >= program.count) {
        return RESULT_LINE_NOT_FOUND_ERROR;  
    }

    return program.lines[index].line_number;
}

ResultCode runProgram(void) {
    sortProgram();
    resetAllVariables();
    resetForStack();
    unsigned char i = 0;
    while (i < program.count) {
        short result = interpret(program.lines[i].text, program.lines[i].line_number, getNextLineNumber);

        if (result < 0) {
            return result;
        }

        if (result > 0) {
            short index = findIndex((unsigned short)result);
            if (index < 0) {
                return RESULT_LINE_NOT_FOUND_ERROR;
            }

            i = (unsigned char)index;
            continue;
        }

        i++;
    }

    return RESULT_OK;
}

ResultCode listProgram(void) {
    sortProgram();
    for (unsigned char i = 0; i < program.count; i++) {
        print(program.lines[i].line_number, FALSE);
        putchar(' ');
        print(program.lines[i].text, TRUE);
    }

    return RESULT_OK;
}

