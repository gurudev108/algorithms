#include <stdio.h>

void recursiveFunction(int depth) {
    char buffer[1024]; // A local buffer to consume stack space

    printf("Current stack depth: %d\n", depth);

    // Recursive call that increases the stack depth
    recursiveFunction(depth + 1);
}

int main() {
    // Start the recursive function with an initial depth of 1
    recursiveFunction(1);

    return 0;
}

