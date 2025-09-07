#include "program.h"
#include "error.h"
#include "common.h"

int main(void) {
    printLine("Minimal BASIC Interpreter");
    printLine("-EXIT to quit");
    printLine("-RUN to run the program");
    printLine("-NEW to clear program");
    printLine("-LIST to list code");

    if (initProgram() != RESULT_OK) return -1;

    ResultCode res = runREPL();

    if (res == RESULT_OK) printLine("Program ran successfully");
    else if (res == RESULT_PRG_STOPPED) printLine("Program stopped by user");
    else printLine("Unknown error");

    freeProgram();
    return 0;
}
