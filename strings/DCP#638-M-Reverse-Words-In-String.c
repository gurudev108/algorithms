/* 
DCP#638 [Medium] Google - Reverse words in a string

Input : "hello world here"
Output: "here world hello"

Follow-up: Given a mutable string representation, can you perform this operation
in-place?

*/
#include<stdio.h>
#include<string.h>

char* reverse(char *str, int start, int end)
{
  for (int i = start; i<= end; i++)
  {
    char temp = str[end - i];
    str[end] = str[i];
    str[i] = temp;
  }
  return str;
}

int main()
{
  char str[] = "hello world here";
  int len = strlen(str);
  int len1 = sizeof(str)/sizeof(str[0]);
  reverse(str, 0, sizeof(str)/sizeof(str[0]));
  printf("\nOutput = %s len %d %d", str, len, len1);
  return 0;
}
 

