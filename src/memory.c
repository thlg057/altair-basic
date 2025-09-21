#include "memory.h"

#define MAX_VARIABLES 260
#define NULL ((void*)0)
static float variables[MAX_VARIABLES];

int getIndex(const char *name) {
    if (!name || name[0] < 'A' || name[0] > 'Z') return -1;

    if (name[1] == '\0') {
        return (name[0] - 'A') * 10;
    }

    if (name[2] != '\0' || name[1] < '0' || name[1] > '9') return -1;

    return (name[0] - 'A') * 10 + (name[1] - '0');
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