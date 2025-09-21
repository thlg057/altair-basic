#include "parser.h"
#include "test_utilities.h"
#include <string.h>

int test_parser_arithmetic(void) {
    ParsedArg args[] = {
        { ARG_TYPE_NUMBER, "2" },
        { ARG_TYPE_OPERATOR, "+" },
        { ARG_TYPE_NUMBER, "3" },
        { ARG_TYPE_OPERATOR, "*" },
        { ARG_TYPE_NUMBER, "5" }
    };
    float result = 0;
    ResultCode rc = evalExpression(args, 5, NULL, &result, NULL);
    ASSERT_INT_EQ(rc, RESULT_OK, "Arithmetic eval should succeed");
    ASSERT(result == 17, "2 + 3 * 5 should be 17");
    return TEST_OK;
}

int test_parser_concat(void) {
    ParsedArg args[] = {
        { ARG_TYPE_STRING, "Hello" },
        { ARG_TYPE_OPERATOR, "+" },
        { ARG_TYPE_NUMBER, "1" }
    };
    char result[64] = {0};
    ResultCode rc = evalExpression(args, 3, result, NULL, NULL);
    ASSERT_INT_EQ(rc, RESULT_OK, "Concat eval should succeed");
    ASSERT_STR_EQ(result, "Hello1", "Concat result should be Hello1");
    return TEST_OK;
}

int test_parser_comparison_true(void) {
    ParsedArg args[] = {
        { ARG_TYPE_NUMBER, "2" },
        { ARG_TYPE_OPERATOR, "+" },
        { ARG_TYPE_NUMBER, "3" },
        { ARG_TYPE_OPERATOR, "=" },
        { ARG_TYPE_NUMBER, "5" }
    };
    int result = 0;
    ResultCode rc = evalExpression(args, 5, NULL, NULL, &result);
    ASSERT_INT_EQ(rc, RESULT_OK, "Comparison eval should succeed");
    ASSERT(result == 1, "2 + 3 = 5 should be true");
    return TEST_OK;
}

int test_parser_comparison_false(void) {
    ParsedArg args[] = {
        { ARG_TYPE_NUMBER, "2" },
        { ARG_TYPE_OPERATOR, "+" },
        { ARG_TYPE_NUMBER, "3" },
        { ARG_TYPE_OPERATOR, "=" },
        { ARG_TYPE_NUMBER, "4" }
    };
    int result = 1;
    ResultCode rc = evalExpression(args, 5, NULL, NULL, &result);
    ASSERT_INT_EQ(rc, RESULT_OK, "Comparison eval should succeed");
    ASSERT(result == 0, "2 + 3 = 4 should be false");
    return TEST_OK;
}