#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

int main() {
    char inputString[100];

    printf("Enter a string: ");
    scanf("%s", inputString);

    int len = strlen(inputString);

    // Sort the string using qsort
    qsort(inputString, len, sizeof(char), compare);

    printf("Sorted string: %s\n", inputString);

    return 0;
}

