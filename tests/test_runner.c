#include <stdio.h>

// Déclarations des tests
int test_errorModule(void);
int test_memory(void);
int test_tokenize_basic(void);
int test_tokenize_operators(void);
int test_interpret_end(void);
int test_interpret_print(void);
int test_interpret_print_bonjour(void);
int test_interpret_print_bonjour1(void);
int test_interpret_goto(void);
int test_interpret_if_true_goto(void);      // Ajouté
int test_interpret_if_false_goto(void);     // Ajouté
int test_repl_init_free(void);
int test_parser_arithmetic(void);
int test_parser_concat(void);
int test_parser_comparison_true(void);
int test_parser_comparison_false(void);
int test_interpret_for_missing_equal(void);
int test_interpret_for_wrong_equal(void);
int test_interpret_for_missing_to(void);
int test_interpret_for_step_without_value(void);
int test_interpret_for_step_zero(void);
int test_interpret_for_too_few_args(void);
int test_interpret_next_empty_stack(void);
int test_interpret_next_wrong_variable(void);
int test_interpret_for_simple_setup(void);
int test_interpret_for_with_step(void);
int test_interpret_next_continue_loop(void);
int test_interpret_next_exit_loop(void);
int test_interpret_next_negative_step(void);
int test_reset_all_variables(void); 
int test_tokenize_negative_numbers(void);

typedef int (*TestFunc)(void);

typedef struct {
    const char* name;
    TestFunc func;
} TestCase;

int main(void) {
    TestCase tests[] = {
        { "Module error", test_errorModule },
        { "Module memory", test_memory },
        { "Token basic", test_tokenize_basic },
        { "Token operators", test_tokenize_operators },
        { "Interpreter END", test_interpret_end },
        { "Interpreter PRINT", test_interpret_print },
        { "Interpreter PRINT BONJOUR", test_interpret_print_bonjour },
        { "Interpreter PRINT BONJOUR + 1", test_interpret_print_bonjour1 },
        { "Interpreter GOTO", test_interpret_goto },
        { "Interpreter IF comparaison true", test_parser_comparison_true },
        { "Interpreter IF comparaison false", test_parser_comparison_false },
        { "REPL init/free", test_repl_init_free },
        { "Parser arithmetic", test_parser_arithmetic },
        { "Parser concat", test_parser_concat },
        { "Parser comparison true", test_parser_comparison_true },
        { "Parser comparison false", test_parser_comparison_false },
        { "Interpreter FOR missing equal", test_interpret_for_missing_equal },
        { "Interpreter FOR wrong equal", test_interpret_for_wrong_equal },
        { "Interpreter FOR missing TO", test_interpret_for_missing_to },
        { "Interpreter FOR step without value", test_interpret_for_step_without_value },
        { "Interpreter FOR step zero", test_interpret_for_step_zero },
        { "Interpreter FOR too few args", test_interpret_for_too_few_args },
        { "Interpreter NEXT empty stack", test_interpret_next_empty_stack },
        { "Interpreter NEXT wrong variable", test_interpret_next_wrong_variable },
        { "Interpreter FOR simple setup", test_interpret_for_simple_setup },
        { "Interpreter FOR with step", test_interpret_for_with_step },
        { "Interpreter NEXT continue loop", test_interpret_next_continue_loop },
        { "Interpreter NEXT exit loop", test_interpret_next_exit_loop },
        { "Interpreter NEXT negative step", test_interpret_next_negative_step },
        { "Reset all variables", test_reset_all_variables },
        { "Token negative numbers", test_tokenize_negative_numbers }
    };

    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    size_t passed = 0;

    for (size_t i = 0; i < numTests; i++) {
        // printf("Running test: %s...\n", tests[i].name);
        if (tests[i].func() == 0) {
            printf("[PASS] %s\n", tests[i].name);
            passed++;
        } else {
            printf("[FAIL] %s\n", tests[i].name);
        }
    }

    printf("\nSummary: %zu/%zu tests passed.\n", passed, numTests);

    return (passed == numTests) ? 0 : 1;
}
