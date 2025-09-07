#include "basic_repl.h"
#include "error.h"
#include "common.h"
#include "program.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>   // <-- pour free() et malloc()/strdup()

#define LINE_MAX 80

ResultCode initREPL(void) {
    return RESULT_OK;
}

ResultCode freeREPL(void) {
    return RESULT_OK;
}

ResultCode runREPL(void) {
    char line[LINE_MAX];

    while (1) {
        print("> ", FALSE);
        if (!fgets(line, LINE_MAX, stdin)) return RESULT_PRG_STOPPED;

        // strip newline
        line[strcspn(line, "\r\n")] = 0;

        if (strCaseCmp(line, "EXIT") == 0 || strCaseCmp(line, "STOP") == 0)
        {
            return RESULT_PRG_STOPPED;
        }

        if (strCaseCmp(line, "NEW") == 0) {
            ResultCode res = clearProgram();
            if (res != RESULT_OK) {
                print(resultCodeToString(res), TRUE);
            }
    
            continue;
        }

        if (strCaseCmp(line, "LIST") == 0) {
            ResultCode res = listProgram();
            if (res != RESULT_OK) {
                print(resultCodeToString(res), TRUE);
            }

            continue;
        }

        if (strCaseCmp(line, "RUN") == 0) {
            print("run program", TRUE);
            ResultCode res = runProgram();
            if (res != RESULT_OK) {
                print(resultCodeToString(res), TRUE);
            }

            continue;
        }

        if (strlen(line) > 0) {
            ResultCode res = addLine(line);
            if (res != RESULT_OK) {
                print(resultCodeToString(res), TRUE);
            }
        }
    }
}
