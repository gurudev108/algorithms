/*

Expand around center approach
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int expandAroundCenter(char* s, int left, int right);

// Function to find the longest palindromic substring
char* longestPalindromicSubstring(char* s) {
    int len = strlen(s);
    
    if (len < 2) {
        return s;
    }

    int start = 0; // Starting index of the longest palindromic substring
    int end = 0;   // Ending index of the longest palindromic substring

    for (int i = 0; i < len; ++i) {
        // Check for odd length palindromes
        int len1 = expandAroundCenter(s, i, i);
        // Check for even length palindromes
        int len2 = expandAroundCenter(s, i, i + 1);

        // Find the maximum length between the two
        int maxLength = len1 > len2 ? len1 : len2;

        // Update the start and end indices if a longer palindrome is found
        if (maxLength > end - start) {
            start = i - (maxLength - 1) / 2;
            end = i + maxLength / 2;
        }
    }

    // Create a substring based on the start and end indices
    char* result = (char*)malloc((end - start + 2) * sizeof(char));
    strncpy(result, s + start, end - start + 1);
    result[end - start + 1] = '\0';

    return result;
}

// Helper function to expand around the center and find the length of a palindrome
int expandAroundCenter(char* s, int left, int right) {
    while (left >= 0 && right < strlen(s) && s[left] == s[right]) {
        --left;
        ++right;
    }
    return right - left - 1;
}

// Main function for testing
int main() {
    char s[] = "babad";
    char* result = longestPalindromicSubstring(s);

    printf("Input: %s\n", s);
    printf("Output: %s\n", result);

    // Don't forget to free the allocated memory
    free(result);

    return 0;
}

