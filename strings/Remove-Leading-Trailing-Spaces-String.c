#include <stdio.h>
#include <string.h>

// Function to remove leading and trailing spaces from a string
void removeSpaces(char* str) {
    int length = strlen(str);

    // Remove leading spaces
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n') {
        start++;
    }

    // Remove trailing spaces
    int end = length - 1;
    while (end > start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }

    // Shift the remaining characters to the beginning of the string
    for (int i = start; i <= end; ++i) {
        str[i - start] = str[i];
    }

    // Null-terminate the modified string
    str[end - start + 1] = '\0';
}

int main() {
    // Maximum length of the input string
    #define MAX_LENGTH 100

    // Declare a character array to store the input string
    char inputString[MAX_LENGTH];

    // Read the input string
    printf("Enter a string: ");
    fgets(inputString, MAX_LENGTH, stdin);

    // Remove leading and trailing spaces
    removeSpaces(inputString);

    // Print the modified string
    printf("Modified string: \"%s\"\n", inputString);

    return 0;
}

