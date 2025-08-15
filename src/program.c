#include "program.h"
#include "error.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // <-- pour free() et malloc()/strdup()

#define LINE_MAX 80
#define MAX_LINES 100

static char* program[MAX_LINES];
static int lineCount = 0;

ResultCode initProgram(void) {
    lineCount = 0;
    return RESULT_OK;
}

ResultCode freeProgram(void) {
    for (int i = 0; i < lineCount; i++) {
        free(program[i]);
    }
    lineCount = 0;
    return RESULT_OK;
}

static void addProgramLine(const char* line) {
    if (lineCount < MAX_LINES) {
        program[lineCount] = strdup(line);
        lineCount++;
    }
}

static void listProgram(void) {
    for (int i = 0; i < lineCount; i++) {
        printLine(program[i]);
    }
}

ResultCode runREPL(void) {
    char line[LINE_MAX];

    while (1) {
        putchar('>'); putchar(' '); // minimal prompt
        if (!fgets(line, LINE_MAX, stdin)) return RESULT_PRG_STOPPED;

        // strip newline
        line[strcspn(line, "\r\n")] = 0;

        if (myStrCaseCmp(line, "EXIT") == 0 || myStrCaseCmp(line, "STOP") == 0)
            return RESULT_PRG_STOPPED;

        if (myStrCaseCmp(line, "NEW") == 0) {
            lineCount = 0;
            printLine("New program cleared");
            continue;
        }

        if (myStrCaseCmp(line, "LIST") == 0) {
            listProgram();
            continue;
        }

        if (myStrCaseCmp(line, "RUN") == 0) {
            for (int i = 0; i < lineCount; i++) {
                printLine(program[i]);
            }
            continue;
        }

        if (strlen(line) > 0) addProgramLine(line);
    }
}
