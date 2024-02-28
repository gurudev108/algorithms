/* NOT WORKING - Segmentation fault
https://man7.org/linux/man-pages/man3/qsort.3.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare(const void* p1, const void* p2)
{
  return strcmp(*(char*)p1, *(char*)p2);
}
int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s <string> \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //qsort(&argv[1], argc-1, sizeof(char *), cmpstringp);
  qsort(&argv[1], strlen(argv[1]), sizeof(char), compare);
  for (size_t j=1; j<argc; j++)
  {
    printf("%s", argv[j]);
    exit(EXIT_SUCCESS);
  }
}
