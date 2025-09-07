#include <stdio.h>

// Déclarations des tests
int test_errorModule(void);
int test_memory(void);
int test_tokenize_basic(void);
int test_tokenize_operators(void);
int test_interpret_end(void);
int test_interpret_print(void);
int test_interpret_goto(void);
int test_repl_init_free(void);

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
        { "Interpreter GOTO", test_interpret_goto },
        { "REPL init/free", test_repl_init_free }
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
