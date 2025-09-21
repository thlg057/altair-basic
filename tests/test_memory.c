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

    return TEST_OK;
}

int test_reset_all_variables(void) {
    // Initialise quelques variables avec des valeurs non-nulles
    float* varA = getVariable("A");
    float* varB5 = getVariable("B5");
    float* varZ = getVariable("Z");
    float* varZ9 = getVariable("Z9");
    
    ASSERT(varA != NULL && varB5 != NULL && varZ != NULL && varZ9 != NULL, 
           "All test variables should be accessible");
    
    *varA = 42.0f;
    *varB5 = -123.45f;
    *varZ = 3.14f;
    *varZ9 = 999.0f;
    
    // Vérifie que les valeurs sont bien assignées
    ASSERT(*varA == 42.0f, "Variable A should have value 42.0");
    ASSERT(*varB5 == -123.45f, "Variable B5 should have value -123.45");
    ASSERT(*varZ == 3.14f, "Variable Z should have value 3.14");
    ASSERT(*varZ9 == 999.0f, "Variable Z9 should have value 999.0");
    
    // Reset toutes les variables
    resetAllVariables();
    
    // Vérifie que toutes les variables sont remises à 0
    ASSERT(*varA == 0.0f, "Variable A should be reset to 0");
    ASSERT(*varB5 == 0.0f, "Variable B5 should be reset to 0");
    ASSERT(*varZ == 0.0f, "Variable Z should be reset to 0");
    ASSERT(*varZ9 == 0.0f, "Variable Z9 should be reset to 0");
    
    // Teste quelques autres variables pour s'assurer qu'elles sont aussi à 0
    ASSERT(*getVariable("M") == 0.0f, "Variable M should be reset to 0");
    ASSERT(*getVariable("C3") == 0.0f, "Variable C3 should be reset to 0");
    
    return TEST_OK;
}
