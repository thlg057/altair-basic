#include "token.h"
#include "test_utilities.h"

int test_tokenize_basic(void) {
    char keyword[MAX_TOKEN_LEN];
    ParsedArg args[4];

    // Test: PRINT "HELLO", 123
    short count = tokenize("PRINT \"HELLO\" 123", keyword, args, 4);
    ASSERT_STR_EQ(keyword, "PRINT", "Keyword should be PRINT");
    ASSERT_INT_EQ(count, 2, "Should parse 2 arguments");
    ASSERT_INT_EQ(args[0].type, ARG_TYPE_STRING, "First arg is string");
    ASSERT_STR_EQ(args[0].value, "HELLO", "First arg value");
    ASSERT_INT_EQ(args[1].type, ARG_TYPE_NUMBER, "Second arg is number");
    ASSERT_STR_EQ(args[1].value, "123", "Second arg value");
    return 0;
}

int test_tokenize_operators(void) {
    char keyword[MAX_TOKEN_LEN];
    ParsedArg args[4];

    short count = tokenize("LET A = 5", keyword, args, 4);
    ASSERT_STR_EQ(keyword, "LET", "Keyword should be LET");
    ASSERT_INT_EQ(count, 3, "Should parse 3 arguments");
    ASSERT_INT_EQ(args[1].type, ARG_TYPE_OPERATOR, "Second arg is operator");
    ASSERT_STR_EQ(args[1].value, "=", "Operator should be =");
    return 0;
}