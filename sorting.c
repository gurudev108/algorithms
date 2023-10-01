/* This file contains my experiments with sorting 
1. Insertion Sort
2. Merge Sort
3. Bubble Sort
4. Quick Sort
*/

#include<stdio.h> // for printf
#include<stdbool.h>

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
   key = A[j]

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

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
  
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    printf("\nmerge low:%d mid:%d high:%d", l, m, r);
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
  printf("\nmergeSort low:%d high:%d", l, r);
    if (l < r) {
        int m = (r + l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
    else
    {
      printf("\nreturn");
      return;
    }
}

// Partition the array using the last element as the pivot
int partition(int arr[], int low, int high)
{
    // Choosing the pivot
    int pivot = arr[high];
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int partition1(int arr[], int p, int r)
{
  x=arr[p];
  i=p-1;
  j=r+1;  
  while(arr[j] >x)
  {
    j--;
  }
  while(arr[i] <x)
  {
    i++;
  }
  if (i<j)


}
 
void quicksort1(int arr[], int p, int r)
{
  if (p<r)
  {
    int q = partition1(arr, p, r);
    quicksort1(arr, p,q);
    quicksort1(arr, q+1, r);
  }
}

// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
  int in_arr[] = {9,5,0,-2,4,6,7,2};
  int len = sizeof(in_arr)/sizeof(int);
  print_array(in_arr, len);
  printf("\n Running Sort...\n");
 
 // insertion_sort(in_arr, len);

//  mergeSort(in_arr, 0, len-1);
 
 // bubbleSort(in_arr, len);

  quickSort(in_arr, 0, len-1);
  print_array(in_arr, len);

  return 0;
}
