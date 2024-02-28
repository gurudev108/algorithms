#include <stdio.h>

/*
ASCII value of upper case and lower case different by 32 which can be either added 
or subtracted by either setting 6th bit or reseting it. 

SPACE - 32

0 - 48
9 - 57

A - 65
Z - 90

_ - 95

a - 97
z - 122

*/

/* mask = 11011111 = 95 which is ACII value of '_' */
char lower_to_upper(char ch)
{
  return ch &= '_';
}

/* mask = 00100000 = 32 which is ASCII value of ' ' */
char upper_to_lower(char ch) 
{
  return ch |= ' ';
}

int main()
{
  printf("%c", lower_to_upper('a'));
  printf("%c", lower_to_upper('b'));
  printf("%c", lower_to_upper('c'));
  printf("%c", lower_to_upper('d'));

  printf("\n%c", upper_to_lower('A'));
  printf("%c", upper_to_lower('B'));
  printf("%c", upper_to_lower('C'));
  printf("%c", upper_to_lower('D'));
  return 0;
}
