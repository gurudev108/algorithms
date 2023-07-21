/* This file contains my experiments with sorting */

#include<stdio.h> // for printf

void print_array(int* in_arr, int len)
{
  printf("\nPrinting array of size:%d: ", len);
  for (int i=0; i<len; i++)
  {
    printf(" %d", in_arr[i]);
  }
}

/* INSERTION SORT - Insert at the right place
At any instant array is sorted from 0 to j-1. We need to insert A[j]
at the right place using i which will loop back from j-1 to 0.  
INPUT - Input array, input array size, 
Output - output array, output array size

   3 4 8 5 1 0 2 6 
         j>>
     <<i

*/
void insertion_sort(int* A, int len) 
{
  int key = 0, i=0;
  for(int j=1; j<len; j++)
  {
    i = j-1;
    key = A[j];
    while ((i>=0) && (key < A[i]))
    {
      A[i+1] = A[i];
      i--;
    }
    A[i+1] = key;
    print_array(A, len);
  } 
}



int main()
{
  int in_arr[] = {9,5,0,-2,4,6,7,2};
  int len = sizeof(in_arr)/sizeof(int);
  print_array(in_arr, len);
  printf("\n Running Insertion Sort...\n");
  insertion_sort(in_arr, len);
  print_array(in_arr, len);

  return 0;
}
