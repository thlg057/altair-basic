#include "interpreter.h"
#include "error.h"
#include "test_utilities.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>

// Mock function pour getNextLine (pour les tests)
static short mock_getNextLine(unsigned short current_line) {
    return current_line + 10; // Simule une ligne suivante
}

int test_interpret_end(void) {
    ASSERT_INT_EQ(interpret("END", 0, NULL), RESULT_PRG_STOPPED, "END should stop program");
    ASSERT_INT_EQ(interpret("STOP", 0, NULL), RESULT_PRG_STOPPED, "STOP should stop program");
    return TEST_OK;
}

int test_interpret_print(void) {
    ASSERT_INT_EQ(interpret("PRINT \"OK\"", 0, NULL), 0, "PRINT should succeed");
    return TEST_OK;
}

int test_interpret_goto(void) {
    ASSERT_INT_EQ(interpret("GOTO 100", 0, NULL), 100, "GOTO should return line number");
    ASSERT_INT_EQ(interpret("GOTO 42", 0, NULL), 42, "GOTO should return line number");
    return TEST_OK;
}

int test_interpret_print_bonjour(void) {
    char buffer[128] = {0};
    FILE* f = fopen("test_out.txt", "w+");
    if (!f) return 1;

    int saved_fd = redirectStdoutToFile(f);
    interpret("PRINT \"Bonjour\"", 0, NULL);
    fflush(stdout);
    restoreStdoutFd(saved_fd);
    fclose(f);

    if (readFileToBuffer("test_out.txt", buffer, sizeof(buffer))) return 1;
    remove("test_out.txt");

    removeNewline(buffer);

    ASSERT(strcmp(buffer, "Bonjour") == 0, "PRINT \"Bonjour\" should output Bonjour");
    return TEST_OK;
}

int test_interpret_print_bonjour1(void) {
    char buffer[128] = {0};
    FILE* f = fopen("test_out.txt", "w+");
    if (!f) return 1;

    int saved_fd = redirectStdoutToFile(f);
    interpret("PRINT \"Bonjour\" + 1", 0, NULL);
    fflush(stdout);
    restoreStdoutFd(saved_fd);
    fclose(f);

    if (readFileToBuffer("test_out.txt", buffer, sizeof(buffer))) return 1;
    remove("test_out.txt");

    removeNewline(buffer);

    ASSERT(strcmp(buffer, "Bonjour1") == 0, "PRINT \"Bonjour\" + 1 should output Bonjour1");
    return TEST_OK;
}

int test_interpret_if_true_goto(void) {
    float* a = getVariable("A");
    if (!a) return TEST_ERROR;
    *a = 0;
    int result = interpret("IF A = 0 GOTO 20", 0, NULL);
    ASSERT_INT_EQ(result, 20, "IF A = 0 GOTO 20 (A=0) should return 20");
    return TEST_OK;
}

int test_interpret_if_false_goto(void) {
    float* a = getVariable("A");
    if (!a) return TEST_ERROR;
    *a = 1;
    int result = interpret("IF A = 0 GOTO 20", 0, NULL);
    ASSERT_INT_EQ(result, RESULT_OK, "IF A = 0 GOTO 20 (A=1) should return RESULT_OK");
    return TEST_OK;
}

// Tests FOR/NEXT
int test_interpret_for_missing_equal(void) {
    int result = interpret("FOR I TO 10", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_SYNTAX_ERROR, "FOR without = should return syntax error");
    return TEST_OK;
}

int test_interpret_for_wrong_equal(void) {
    int result = interpret("FOR I < 1 TO 10", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_SYNTAX_ERROR, "FOR with < instead of = should return syntax error");
    return TEST_OK;
}

int test_interpret_for_missing_to(void) {
    int result = interpret("FOR I = 1 AT 10", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_SYNTAX_ERROR, "FOR with AT instead of TO should return syntax error");
    return TEST_OK;
}

int test_interpret_for_step_without_value(void) {
    int result = interpret("FOR I = 1 TO 10 STEP", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_SYNTAX_ERROR, "FOR with STEP but no value should return syntax error");
    return TEST_OK;
}

int test_interpret_for_step_zero(void) {
    int result = interpret("FOR I = 1 TO 10 STEP 0", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_SYNTAX_ERROR, "FOR with STEP 0 should return syntax error");
    return TEST_OK;
}

int test_interpret_for_too_few_args(void) {
    int result = interpret("FOR I = 1", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_SYNTAX_ERROR, "FOR with too few arguments should return syntax error");
    return TEST_OK;
}

int test_interpret_for_simple_setup(void) {
    resetAllVariables();
    resetForStack(); // Ajoute ceci pour être cohérent
    
    int result = interpret("FOR I = 1 TO 3", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_OK, "FOR I = 1 TO 3 should succeed");
    
    float* var = getVariable("I");
    ASSERT(var && *var == 1.0f, "FOR should initialize I to 1");
    
    return TEST_OK;
}

int test_interpret_for_with_step(void) {
    resetAllVariables();
    resetForStack(); // Ajoute ceci aussi
    
    int result = interpret("FOR I = 1 TO 10 STEP 2", 10, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_OK, "FOR I = 1 TO 10 STEP 2 should succeed");
    
    float* var = getVariable("I");
    ASSERT(var && *var == 1.0f, "FOR should initialize I to 1");
    
    return TEST_OK;
}

int test_interpret_next_continue_loop(void) {
    resetAllVariables();
    resetForStack(); // Ajoute ceci aussi
    
    // Setup FOR I = 1 TO 3
    interpret("FOR I = 1 TO 3", 10, mock_getNextLine);
    
    // First NEXT: I should go from 1 to 2, continue loop
    int result = interpret("NEXT I", 30, mock_getNextLine);
    float* var = getVariable("I");
    ASSERT(var && *var == 2.0f, "First NEXT should increment I to 2");
    ASSERT(result == 20, "NEXT should return next line after FOR");
    
    return TEST_OK;
}

int test_interpret_next_exit_loop(void) {
    resetAllVariables();
    resetForStack(); // Ajoute ceci
    
    // Setup FOR I = 1 TO 2 (boucle courte)
    interpret("FOR I = 1 TO 2", 10, mock_getNextLine);
    
    // Vérifier l'état initial
    float* var = getVariable("I");
    ASSERT(var && *var == 1.0f, "FOR should initialize I to 1");
    
    // First NEXT: I = 2, continue (car 2 <= 2)
    int result1 = interpret("NEXT I", 30, mock_getNextLine);
    ASSERT(var && *var == 2.0f, "First NEXT should increment I to 2");
    ASSERT_INT_EQ(result1, 20, "First NEXT should continue loop");
    
    // Second NEXT: I = 3, should exit loop (car 3 > 2)
    int result2 = interpret("NEXT I", 30, mock_getNextLine);
    ASSERT(var && *var == 3.0f, "Final NEXT should increment I to 3");
    ASSERT_INT_EQ(result2, RESULT_OK, "NEXT should exit loop and return OK");
    
    return TEST_OK;
}

int test_interpret_next_empty_stack(void) {
    resetAllVariables();
    int result = interpret("NEXT I", 30, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_ERROR, "NEXT without matching FOR should return error");
    return TEST_OK;
}

int test_interpret_next_wrong_variable(void) {
    resetAllVariables();
    // Setup FOR I
    interpret("FOR I = 1 TO 3", 10, mock_getNextLine);
    int result = interpret("NEXT J", 30, mock_getNextLine);
    ASSERT_INT_EQ(result, RESULT_ERROR, "NEXT with wrong variable should return error");
    return TEST_OK;
}

int test_interpret_next_negative_step(void) {
    resetForStack();
    resetAllVariables();
    
    float* var = getVariable("I");

    // Setup FOR I = 5 TO 3 STEP -1
    int setup_result = interpret("FOR I = 5 TO 3 STEP -1", 10, mock_getNextLine);
    
    // Vérifier l'état initial
    ASSERT(var && *var == 5.0f, "FOR should initialize I to 5");
    
    // First NEXT: I should go from 5 to 4, continue (car 4 >= 3)
    int result = interpret("NEXT I", 30, mock_getNextLine);
    ASSERT(var && *var == 4.0f, "NEXT with negative step should decrement I to 4");
    ASSERT_INT_EQ(result, 20, "NEXT should continue loop");
    
    return TEST_OK;
}