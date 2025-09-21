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
    return TEST_OK;
}

int test_tokenize_operators(void) {
    char keyword[MAX_TOKEN_LEN];
    ParsedArg args[4];

    short count = tokenize("LET A = 5", keyword, args, 4);
    ASSERT_STR_EQ(keyword, "LET", "Keyword should be LET");
    ASSERT_INT_EQ(count, 3, "Should parse 3 arguments");
    ASSERT_INT_EQ(args[1].type, ARG_TYPE_OPERATOR, "Second arg is operator");
    ASSERT_STR_EQ(args[1].value, "=", "Operator should be =");
    return TEST_OK;
}

int test_tokenize_negative_numbers(void) {
    char keyword[MAX_TOKEN_LEN];
    ParsedArg args[8];

    // Test: FOR I = 5 TO 3 STEP -1
    short count = tokenize("FOR I = 5 TO 3 STEP -1", keyword, args, 8);
    ASSERT_STR_EQ(keyword, "FOR", "Keyword should be FOR");
    ASSERT_INT_EQ(count, 7, "Should parse 7 arguments");
    
    ASSERT_STR_EQ(args[0].value, "I", "args[0] should be I");
    ASSERT_STR_EQ(args[1].value, "=", "args[1] should be =");
    ASSERT_STR_EQ(args[2].value, "5", "args[2] should be 5");
    ASSERT_STR_EQ(args[3].value, "TO", "args[3] should be TO");
    ASSERT_STR_EQ(args[4].value, "3", "args[4] should be 3");
    ASSERT_STR_EQ(args[5].value, "STEP", "args[5] should be STEP");
    ASSERT_STR_EQ(args[6].value, "-1", "args[6] should be -1");
    ASSERT_INT_EQ(args[6].type, ARG_TYPE_NUMBER, "args[6] should be a number");
    
    return TEST_OK;
}