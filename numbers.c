#include<stdio.h>
#include<math.h>
#include<limits.h> // for INT_MAX
#include<string.h> // for strlen

/* Leetcode Medium - Reverse Integer 
https://leetcode.com/problems/reverse-integer/description/

<<<< result = (result*10)+ mod>>>>>
*/

int reverse(int x){
    int result = 0;
    int tmp = 0;
    while(x)
    {
      tmp = x%10;
      x = x/10;
      if (result > INT_MAX/10) return 0;
      if (result < -INT_MAX/10) return 0;
// Important LOGIC of picking up numbers using math
      result = (result*10) + tmp;
      printf("\n tmp= %d x=%d result=%d INT_MAX=%d", tmp, x, result, INT_MAX);
    }
  return result;
}

/* Leetcode Medium - String to Integer ATOI
https://leetcode.com/problems/string-to-integer-atoi/description/
*/
int myAtoi(char * s){
  int number = 0;
  char ch = '0';
  int sign = 1;
  int len = strlen(s);
  for (int i = 0; i<len; i++)
  {
    ch = s[i];
    if ((ch == '-') && (number == 0))
    {
      sign = -1;
      continue;
    }
    printf("ch=%c", ch);
    if (ch == ' ')
    {
      continue;
    }
    if ((ch <48) || (ch>57))
    {
      break;
    } 
    number = (number*10)+ (ch-48);
  }
  return number*sign;
}

void reverse_main()
{
  int x = 123;
  printf ("Reverse of %d is %d\n", x, reverse(x));
  x = -32845;
  printf ("Reverse of %d is %d\n", x, reverse(x));
  x = 1534236469;
  printf ("Reverse of %d is %d\n", x, reverse(x));
}

void myAtoi_main()
{
  printf("myAToi of '123' =%d\n", myAtoi("123"));
  printf("myAToi of '-123' =%d\n", myAtoi("-123"));
  printf("myAToi of '-123d' =%d\n", myAtoi("-123d"));
  printf("myAToi of '  -42' =%d\n", myAtoi("  -42"));
  printf("myAToi of '-91283472332' =%d\n", myAtoi("-91283472332"));
}
int main()
{
  //reverse_main();
  myAtoi_main();

  return 0;
}
