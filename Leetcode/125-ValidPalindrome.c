/*
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.
*/
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool isValid(char c)
{
    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')))
    {
        return true;
    }
    else 
    {
        return false;
    }
}
bool isUpperCase(char c)
{
    if ((c >= 65 ) && (c <= 90))
      return true;
    else
      return false;
}

char convertLower(char c)
{
  return c+32;
}
bool isPalindrome(char * s){
  int len = strlen(s);
  int l=0, r=len-1;
  while (l<r)
  {
      if (!isValid(s[l]))
      {
          l++;
      }
      if (!isValid(s[r]))
      {
          r--;
      }
      if (isValid(s[l]) && isValid(s[r]))
      {
          if (isUpperCase(s[l]))
            s[l] = convertLower(s[l]);
          if (isUpperCase(s[r]))
            s[r] = convertLower(s[r]);         
          if( s[l] != s[r] ) 
            return false;
          else
          {
            l++;
            r--;
            continue;
          }
      }
  }
  return true;
}

int main()
{
  char str[] = "A man, a plan, a canal: Panama";
  bool flag = false;
  flag = isPalindrome(str);
  printf("Given str %s isPalindrome flag:%d", str, flag);
  return 0;
}
