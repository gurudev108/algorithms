/* Cormen quicksort 

Begin
   2  8  7  1  3  5  6  4
 i p                    r
   j>>                  key

Middle
   2  1  3  8  7  5  6  4
   p     i        j     r

End of for loop
   2  1  3  8  7  5  6  4
   p     i             jr

After last swap
   2  1  3  4  7  5  6  8
   p        -           r

*/

#include <stdio.h>

int partition(int *arr, int p, int r)
{
  int key = arr[r];
  int i= p-1;
  int temp = 0;

  for(int j=p; j<r; j++)  // loop for p to r-1
  {
    if (arr[j]<=key)
    {
      i++;
      /* swap arr[i] arr[j] so that smaller than pivot elements are in [p, i] and
      greater are between [i, j] and[j,r] are yet to be placed*/
      temp = arr[j];
      arr[j] = arr[i];
      arr[i] = temp;
    }
  }
  /* swap a[i+1] and a[r] */
  temp = arr[r];
  arr[r] = arr[i+1];
  arr[i+1] = temp;

  return i+1;
  
}

void print (int *arr, int len)
{
  for (int i=0; i<len; i++)
  {
    printf(" %d", arr[i]);
  }
}

void quicksort(int* arr, int p, int r)
{
  if(p<r)
  {
    int q = partition (arr, p, r);
    quicksort(arr, p, q-1);
    quicksort(arr, q+1, r);
  }
}

int main()
{
  int arr[] = {3,5,2,9,7,5,6,20};
  int len = sizeof(arr)/sizeof(arr[0]);

  print(arr, len);
  quicksort(arr, 0, len-1);
  printf("\nAfter sorting\n");
  print(arr, len);
  return 0;
}
