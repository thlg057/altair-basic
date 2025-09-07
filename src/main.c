#include "basic_repl.h"
#include "error.h"
#include "common.h"

int main(void) {
    printLine("Minimal BASIC Interpreter");
    printLine("> ");

    if (initProgram() != RESULT_OK) return -1;

    ResultCode res = runREPL();

    if (res == RESULT_OK) printLine("Program ran successfully");
    else if (res == RESULT_PRG_STOPPED) printLine("Program stopped by user");
    else printLine("Unknown error");

    freeProgram();
    return 0;
}
