#include "test_common.h"

void restoreStdin(void) {
#ifdef _WIN32
    freopen("CON", "r", stdin);     // Windows console
#else
    freopen("/dev/tty", "r", stdin); // Unix/Linux terminal
#endif
}

void restoreStdout(void) {
#ifdef _WIN32
    freopen("CON", "w", stdout);     // Windows console
#else
    freopen("/dev/tty", "w", stdout); // Unix/Linux terminal
#endif
}
