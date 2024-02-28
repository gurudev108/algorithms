/*
https://leetcode.com/problems/valid-anagram/description/

242. Valid Anagram

Approach
1. Brute Force - Sort the 2 strings and check if they are equal O(nlogn)
2. Check frequency of every letter is same 

Follow up - What if we were to use Unicode Characters
Ans - Use hashtable instead of array coz unicode characters can be a lot
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int compare(const void* a, const void* b)
{
    return (*(char*)a - *(char*)b);
}

/* Approach 1 - Sorting */
bool isAnagram_sorting(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    qsort(s, len_s, sizeof(char), compare);
    qsort(t, len_t, sizeof(char), compare);

    if (strcmp(s,t)==0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void print(int* ptr, int len)
{
  printf("\n");
  for (int i=0; i<len; i++)
  {
    printf("%d ", ptr[i]);
  }
}

/* Approach 2 - using frequency of chars */
bool isAnagram_freq(char* s, char* t)
{
  int counter[26];
  int len_s = strlen(s);
  int len_t = strlen(t);
  memset(counter, 0, sizeof(counter));
  if (len_s != len_t)
  {
    return false;
  }
  print(counter, 26);
  for (int i=0; i<len_s; i++)
  {
    counter[s[i]-'a']++;
    counter[t[i]-'a']--;
  }
  print(counter, 26);
  for (int i=0; i<26; i++)
  {
    //printf("\ncounter[%d]=%d", i, counter[i]);
    if(counter[i] != 0)
    {
      return false;
    }
  }
  return true;
}

int main()
{
  /* Qsort can't work on immutable strings, make a mutable copy */
  char* immutable_str1 = "listen";
  char* immutable_str2 = "silent";

  char* test_str1 = "nl";
  char* test_str2 = "cx";

  int len_str1 = strlen(immutable_str1);
  char* str1 = (char*) malloc(len_str1+1);
  strcpy(str1, immutable_str1);

  int len_str2 = strlen(immutable_str2);
  char* str2 = (char*) malloc(len_str2 + 1);
  strcpy(str2, immutable_str2);

  //bool result = isAnagram_sorting(str1, str2);
  // Immutable strings can be Qsorted
  bool result = isAnagram_freq(immutable_str1, immutable_str2);
  printf("%s %s isAnagram %d", immutable_str1, immutable_str2, result);
  
  result = isAnagram_freq(test_str1, test_str2);
  printf("Immutable strings %s & %s isAnagram %d", test_str1, test_str2, result);
  return 0;
}

