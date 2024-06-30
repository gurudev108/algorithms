/* 
151. Reverse Words in a string
Medium

Output:
Original String: "   the sky is   blue  "
Reversed String: " blue is sky the "
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse a portion of a string from start to end
void reverseSubstring(char* s, int start, int end) {
    while (start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

// Function to reverse the order of words in a string
char* reverseWords(char* s) {
    int length = strlen(s);

    // Step 1: Reverse the entire string
    reverseSubstring(s, 0, length - 1);

    // Step 2: Reverse each individual word
    int start = 0;
    for (int end = 0; end < length; ++end) {
        if (s[end] == ' ') {
            reverseSubstring(s, start, end - 1);
            start = end + 1;
        }
    }
    // Reverse the last word - @TODO Check if we really need it
    reverseSubstring(s, start, length - 1);

    // Step 3: Remove extra spaces
    int i, j;
    for (i = 0, j = 0; s[i]; ++i) {
        while (s[i] == ' ' && s[i + 1] == ' ') {
            ++i;
        }
        s[j++] = s[i];
    }
    s[j] = '\0';

    return s;
}

// Main function for testing
int main() {
    char s[] = "   the sky is   blue  ";
    
    printf("Original String: \"%s\"\n", s);

    // Reverse the order of words in the string
    char* reversedString = reverseWords(s);

    printf("Reversed String: \"%s\"\n", reversedString);

    return 0;
}

