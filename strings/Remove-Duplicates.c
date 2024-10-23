/*
Implement a function that performs in-place string removal of duplicate characters.

Approach:
Use char_set[256] to set boolean of all occurences

Output:
Input String=Programming in C
Output String=Progamin C
*/

#include <stdio.h>
#include <stdbool.h>

void remove_duplicates(char* str)
{
  int index = 0;
  bool char_set[256] = {false};

  for(int i=0; str[i] !='\0'; i++)
  {
    if (char_set[(unsigned char) str[i]] == false)
    {
      char_set[(unsigned char)str[i]] = true;
      str[index++] = str[i];
    }
  }
  str[index] = '\0';
}

int main()
{
  char str[] = "Programming in C";

  printf("\nInput String=%s", str);
  remove_duplicates(str);

  printf("\nOutput String=%s", str);

  return 0;
}
