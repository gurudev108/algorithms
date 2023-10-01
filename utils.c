/* 
Writing utility functions here 
1. Implement your own sizeof operator
2. Demonstrate use of function pointers
3. Demonstrate use of macro and macro functions
*/

#include <stdio.h>
#include <stdint.h>

#define my_sizeof(type) (char*)(&type+1) - (char*)(&type)
int result(int a, int b);

int main()
{
  int x = 1;
  uint64_t y = 0;
  double d = 0;
  unsigned int long z = 0;
  int (*fp) (int, int) = NULL;
  uint16_t hex = 0xffff;
  fp = &result;

  printf("Size of int:%ld uint64:%ld double:%ld unsigned int log:%ld fp:%ld invoke fp=%d\n", 
    my_sizeof(x), my_sizeof(y), my_sizeof(d), my_sizeof(z), my_sizeof(fp), (*fp)(x, 3));

  printf("hex=0xffff %d, hex+1=%d ++hex=%d", hex, hex+1, ++hex);
  hex = -1;

  printf("hex=0xffff %d, hex+1=%d ++hex=%d", hex, hex+1, ++hex);

  return 0;
}

int result (int a, int b)
{
  return a+b;
}
