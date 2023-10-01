/* Bubble sort 

  3. 5. 2. 9. 7. 5. 6. 20
  i>>                   >
  <sorted><i+1        <<j
*/

#include <stdio.h>

void bubblesort(int* arr, int len)
{
  int temp = 0;
  for (int i = 0; i<len; i++)
    for (int j= len-1; j>=i+1; j--)
    {
      if (arr[j]<arr[j-1])
      {
        temp = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = temp;
      }
    }
}

void print (int *arr, int len)
{
  for (int i=0; i<len; i++)
  {
    printf(" %d", arr[i]);
  }
}

int main()
{
  int arr[] = {3,5,2,9,7,5,20, 6};
  int len = sizeof(arr)/sizeof(arr[0]);

  print(arr, len);
  bubblesort(arr, len);
  printf("\nAfter sorting\n");
  print(arr, len);
  return 0;
}
