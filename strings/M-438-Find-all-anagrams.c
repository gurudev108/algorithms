/*
https://leetcode.com/problems/find-all-anagrams-in-a-string/description/
Topics {Array, HashTable, String, SlidingWindow}
438. Find All Anagrams in a String

Example 1:
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Approach
1. Sliding window with array (of frequncy counter) - Time O(n) Space O(1)
2. Sliding window with HashMap - Not implemented
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Approach 1 */
bool isAnagram(char* s, char* t) 
{
  int counter[26];
  int len_s = strlen(s);
  int len_t = strlen(t);
  memset(counter, 0, sizeof(counter));
/*
  if (len_s != len_t)
  {
    return false;
  }
*/

  for (int i=0; i<len_t; i++)
  {
    counter[s[i]-'a']++;
    counter[t[i]-'a']--;
  }

  for (int i=0; i<26; i++)
  {
    if(counter[i] != 0)
    {
      return false;
    }
  }
  return true;
}

int* findAnagrams(char* s, char* p, int* returnSize) {
    int len_s = strlen(s);
    int len_p = strlen(p);
    if (len_s<len_p)
    {
      *returnSize = 0;
        return NULL;
    }
    int* result = (int*)malloc(sizeof(int)*(len_s-len_p+1));
    int index = 0;
    for (int i=0; i<len_s-len_p+1; i++)
    {
        if (isAnagram(&s[i],p))
        {
            result[index] = i;
            //printf("anagram found at i %d index %d", i, index);
            index++;
        }
    }
    *returnSize = index;
    return result;    
}

int main()
{
  char* str1 = "cbaebabacd";
  char* str2 = "abc";
  int size = 0;
  int *result = NULL;

  result = findAnagrams(str1, str2, &size);
  for (int i=0; i<size; i++)
  {
    printf("%d ", result[i]);
  }
 
  return 0;
}
