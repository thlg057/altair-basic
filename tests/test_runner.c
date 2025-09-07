#include <stdio.h>

// Déclarations des tests
int test_errorModule(void);
int test_memory(void);
//int test_init_and_freeProgram(void);

typedef int (*TestFunc)(void);

typedef struct {
    const char* name;
    TestFunc func;
} TestCase;

int main(void) {
    TestCase tests[] = {
        { "Module error", test_errorModule },
        { "Module memory", test_memory }
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
