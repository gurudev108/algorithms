/*
3. Longest substring without repeating characters
Medium

The primary challenge in this problem is to find an efficient way to get all possible longest substrings that contain no duplicate characters. 
To achieve this, we need to take advantage of Hash Table, which checks if a character occurs before quickly.

In the following three approaches (below code is for 2nd approach), we utilize a hash table to guarantee substrings have no repeating characters 
and optimize the algorithm to query possible substrings step by step: 
the first approach is intuitive but may cause a TLE, 
and the second one uses a slide window method to narrow down the search range, 
and the third make further use of HashMap to reduce the search range faster.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char* s)
{
  int len = strlen(s);
  int maxLen = 0;
  int start = 0;
  /* Doubt - 255 or 256 */
  int* map = (int *)malloc(sizeof(int)*256);

  for (int i=0; i<256; i++)
  {
    // initialize all character indices to -1
    map[i] = -1;
  }

  for (int end = 0; end<len; end++)
  {
    if(map[s[end]] != -1)
    {
      // Already present - update start
      // ##IMP - ChatGPT made a mistake here - correcte it by taking the max
      start = map[s[end]] + 1 > start ? map[s[end]] + 1: start;
    }
    map[s[end]] = end;
    if (maxLen < end-start+1)
    {
      maxLen = end-start+1;
    }
    printf("\nstart %d end %d maxLen %d", start, end, maxLen);
  }
  free(map);

  return maxLen;
}

// Main function for testing
int main() {
    //char s[] = "abcabcbb";
//    char s[] = "abba";
    char s[] = "abcdbeaf";
    int result = lengthOfLongestSubstring(s);

    printf("\nInput: %s", s);
    printf("\nLength of the longest substring without repeating characters: %d\n", result);

    return 0;
}



//Above solution is inspired from below chatGPT solution

int lengthOfLongestSubstring1(char* s) {
    int len = strlen(s);

    // Character index array to store the last index of each character in the current window
    int* charIndex = (int*)malloc(256 * sizeof(int));
    for (int i = 0; i < 256; ++i) {
        charIndex[i] = -1; // Initialize all character indices to -1
    }

    int maxLength = 0; // Length of the longest substring without repeating characters
    int start = 0;     // Start index of the current window

    for (int end = 0; end < len; ++end) {
        // If the current character is already in the window, update the start index
        if (charIndex[s[end]] != -1) {
            start = charIndex[s[end]] + 1;
        }

        // Update the index of the current character in the window
        charIndex[s[end]] = end;

        // Update the maximum length of the substring without repeating characters
        if (end - start + 1 > maxLength) {
            maxLength = end - start + 1;
        }
    }

    free(charIndex);

    return maxLength;
}

