#include "basic_repl.h"
#include "error.h"
#include "common.h"

int main(void) {
    print("Minimal BASIC Interpreter", TRUE);
    print("> ", TRUE);

    if (initREPL() != RESULT_OK) return -1;

    ResultCode res = runREPL();
    print(resultCodeToString(res), TRUE);

    freeREPL();
    return 0;
}
