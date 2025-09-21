#include "memory.h"
#include <stddef.h>

#define MAX_VARIABLES (26 * 10)
static float variables[MAX_VARIABLES];

int getIndex(const char *name) {
    if (!name) return -1;
    char c0 = name[0];
    if (c0 < 'A' || c0 > 'Z') return -1;
    
    char c1 = name[1];
    if (c1 == '\0') return (c0 - 'A') * 10;
    
    if (name[2] != '\0' || c1 < '0' || c1 > '9') return -1;
    return (c0 - 'A') * 10 + (c1 - '0');
}

float* getVariable(const char *name) {
    int index = getIndex(name);
    if (index == -1) {
        return NULL;
    }

    return &variables[index];
}

/**
 * Resets all BASIC variables to 0.
 */
void resetAllVariables(void) {
    for (int i = 0; i < MAX_VARIABLES; ++i) {
        variables[i] = 0;
    }
}