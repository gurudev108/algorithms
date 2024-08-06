/*
Function to reverse a string

Original string: Hello, World!
Reversed string: !dlroW ,olleH
*/

#include <stdio.h>
#include <string.h>

// Function to reverse a string
void reverseString(char *str) {
    int n = strlen(str);
    int start = 0;
    int end = n - 1;
    char temp;

    // Swap characters from start to end
    while (start < end) {
        // Swap the characters at start and end
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        // Move towards the middle
        start++;
        end--;
    }
}

int main() {
    // Define a string
    char str[] = "Hello, World!";

    printf("Original string: %s\n", str);

    // Reverse the string
    reverseString(str);

    printf("Reversed string: %s\n", str);

    return 0;
}

