#include "program.h"
#include "error.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // <-- pour free() et malloc()/strdup()

#define MAX_LINES 50
#define MAX_CMDLINE_SIZE 72
#define MAX_LINE_SIZE 80
#define MAX_UNSIGNED_INT 65535

typedef struct {
    unsigned short line_number;
    char text[MAX_CMDLINE_SIZE + 1]; // +1 pour le \0
} BasicLine;

typedef struct {
    BasicLine lines[MAX_LINES];
    unsigned char count; // suffisant car < 255
} BasicProgram;

static BasicProgram program;

short parseLine(const char *input, unsigned short *line_number, char *code, size_t code_size) {
    if (!input || !line_number || !code) {
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

    *line_number = (unsigned short)num;
    while (*input == ' ' || *input == '\t') {
        input++;
    }

    size_t i = 0;
    while (i < code_size - 1 && input[i] != '\0') {
        code[i] = input[i];
        i++;
    }

    code[i] = '\0';
    return RESULT_OK;
}

static short findIndex(unsigned short target_line) {
    for (unsigned char j = 0; j < program.count; j++) {
        if (program.lines[j].line_number == target_line) {
            return j; 
        }
    }
    return RESULT_ERROR;
}

static void sortProgram(void) {
    for (unsigned char i = 1; i < program.count; i++) {
        BasicLine key = program.lines[i];
        char j = i - 1;
        while (j >= 0 && program.lines[j].line_number > key.line_number) {
            program.lines[j + 1] = program.lines[j];
            j--;
        }

        program.lines[j + 1] = key;
    }
}

ResultCode clearProgram(void) {
    program.count = 0;
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
    unsigned short line_number;
    char code[73];
    res = parseLine(line, &line_number, code, sizeof(code));
    if (res != RESULT_OK) {
        return res;
    }

    program.lines[program.count].line_number = line_number;
    strCopyTruncate(program.lines[program.count].text, code, MAX_CMDLINE_SIZE);
    program.count++;
    return RESULT_OK;
}

ResultCode runProgram(void) {
    sortProgram();
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

