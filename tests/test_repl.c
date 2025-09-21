#include "repl.h"
#include "test_utilities.h"

int test_repl_init_free(void) {
    ASSERT_INT_EQ(initREPL(), 0, "initREPL should return RESULT_OK");
    ASSERT_INT_EQ(freeREPL(), 0, "freeREPL should return RESULT_OK");
    return TEST_OK;
}