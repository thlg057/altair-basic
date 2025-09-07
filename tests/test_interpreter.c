#include "interpreter.h"
#include "error.h"           // <-- Ajoute cette ligne
#include "test_utilities.h"

int test_interpret_end(void) {
    ASSERT_INT_EQ(interpret("END"), RESULT_PRG_STOPPED, "END should stop program");
    ASSERT_INT_EQ(interpret("STOP"), RESULT_PRG_STOPPED, "STOP should stop program");
    return 0;
}

int test_interpret_print(void) {
    ASSERT_INT_EQ(interpret("PRINT \"OK\""), 0, "PRINT should succeed");
    return 0;
}

int test_interpret_goto(void) {
    ASSERT_INT_EQ(interpret("GOTO 100"), 100, "GOTO should return line number");
    ASSERT_INT_EQ(interpret("GOTO 42"), 42, "GOTO should return line number");
    return 0;
}