#include "basic_repl.h"
#include "error.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // <-- pour free() et malloc()/strdup()

#define LINE_MAX 80

ResultCode initProgram(void) {
    return RESULT_OK;
}

ResultCode freeProgram(void) {
    return RESULT_OK;
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
            printLine("New program cleared");
            continue;
        }

        if (myStrCaseCmp(line, "LIST") == 0) {
            printLine("Code lines:");
            continue;
        }

        if (myStrCaseCmp(line, "RUN") == 0) {
            printLine("run program");
            continue;
        }

        // if (strlen(line) > 0) addProgramLine(line);
    }
}
