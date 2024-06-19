/*
Daily Coding Problem#788
Write a program that checks whether an integer is a palindrome. For example, 121 is a palindrome, as well as 888. 678 is not a palindrome. Do not convert the integer into a string.
*/

#include<stdio.h>
#include<stdbool.h>

void palindrome(int num)
{
  int remainder = 0;
  printf("input num=%d", num);
  while(num)
  {
    remainder = num%10;
    remainder += remainder*10;
    num = num/10;
  }
  printf("\nReverse of %d is %d", num, remainder);
}
int main()
{
  palindrome(678);
  return 0;
}

