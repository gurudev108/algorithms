/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Given a string and a pattern, find the starting indices of all occurrences of the pattern in the string. For example, given the string "abracadabra" and the pattern "abr", you should return [0, 7].

Verified output:
0 7
*/

#include "stdio.h"
#include "string.h"

void find_all_occurences(char* str, char* pattern, int* indices, int *count)
{
  int len_s = strlen(str);
  int len_p = strlen(pattern);
  int left = 0;
  int right = len_p;
  for(int i=0; i<=len_s-len_p; i++)
  {
    if(strncmp(&str[i], pattern, len_p) == 0)
    {
      indices[*count] = i;
      *count = *count + 1;  
    }
  }
  return;
}

int main()
{
  char str[] = "abracadabra";
  char pattern[] = "abr";
  int count = 0;
  int indices[100];

  find_all_occurences(str, pattern, indices, &count);
  for (int i=0; i<count; i++)
  {
    printf("%d ", indices[i]);
  }
  return 0;
}
