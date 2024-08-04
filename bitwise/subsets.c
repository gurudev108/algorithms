  /*
Example:
   Let, A = {a,b,c} 
   dec  bin   subset
   -----------------
   0 = (000) = {}
   1 = (001) = {c}
   2 = (010) = {b}
   3 = (011) = {b, c}
   4 = (100) = {a}
   5 = (101) = {a, c}
   6 = (110) = {a, b}
   7 = (111) = {a, b, c}

Output:

*/

#include <stdio.h>

int main()
{
  char A[] = {'a', 'b', 'c'};

  int size = sizeof(A)/sizeof(char);  
  int count = 1<<size;

  for (int i = 0; i<count; i++)
  {
    printf("{");
    for (int j=0; j<size; j++)
    {
      if (i & 1<<j)
      {
        printf("%c,", A[j]);
      }
    }
    printf("}");
  } 
}
