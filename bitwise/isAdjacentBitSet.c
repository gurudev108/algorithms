/*
67 in binary is 01000011
Adjacent pair of set bits found
*/

#include <stdio.h>
#include <stdbool.h>
bool check (int n)
{
  // ### IMP
  return n & (n<<1);
}

int main()
{
  int n = 67;
  printf("\n Is Adjacent bit set for %d - %d", n, check(n));
  return 0;
}
