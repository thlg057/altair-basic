#include "memory.h"
#include "test_utilities.h"

int test_memory(void) {
    float *var;

    // Test simple single-letter variables
    var = getVariable("A");
    ASSERT(var != NULL, "Variable A should exist");
    *var = 42.0f;
    ASSERT_INT_EQ(*getVariable("A"), 42, "Variable A value");

    var = getVariable("Z");
    ASSERT(var != NULL, "Variable Z should exist");
    *var = -3.14f;
    ASSERT_INT_EQ((int)(*getVariable("Z")), -3, "Variable Z value (cast to int for test)");

    // Test variables with a digit (A0..Z9)
    var = getVariable("A0");
    ASSERT(var != NULL, "Variable A0 should exist");
    *var = 1.23f;
    ASSERT_INT_EQ((int)(*getVariable("A0")), 1, "Variable A0 value");

    var = getVariable("B5");
    ASSERT(var != NULL, "Variable B5 should exist");
    *var = 99.9f;
    ASSERT_INT_EQ((int)(*getVariable("B5")), 99, "Variable B5 value");

    // Test invalid variable names
    ASSERT(getVariable("a") == NULL, "Lowercase variable should return NULL");
    ASSERT(getVariable("AA") == NULL, "Double-letter variable should return NULL");
    ASSERT(getVariable("Z9x") == NULL, "Too long variable should return NULL");
    ASSERT(getVariable("1A") == NULL, "Variable starting with digit should return NULL");
    ASSERT(getVariable("") == NULL, "Empty string should return NULL");
    ASSERT(getVariable(NULL) == NULL, "NULL pointer should return NULL");

    return 0;
}
