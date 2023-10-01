/* Power Set: Power set P(S) of a set S is the set of all subsets of S.
For example S = {a, b, c} then 
P(s) = {{}, {a}, {b}, {c}, {a,b}, {a, c}, {b, c}, {a, b, c}}.
If S has n elements in it then P(s) will have 2n elements */

#include<stdio.h>
#include<math.h> //for pow

void printPowerSet(char* set, int len)
{
  int power_set_size = pow(2, len);
  for (int i=0; i<power_set_size; i++)
  {
    for (int j=0; j<len; j++)
    {
      if (i & (1<<j))
      {
        printf("%c", set[j]);
      }
    }
    printf("\n");
  }
}


int main()
{
  char set[] = {'a', 'b', 'c'};
  printPowerSet(set, 3);
  return 0;
}
