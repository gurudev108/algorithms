/* This file contains my experiments with sorting 
1. Insertion Sort - good for small data set, simple and less overhead, sorts in order, in place. works piece by piece and not entire data needed in 1 shot. Inefficient for large list. Works well on already somewhat sorted data. Selection and Bubble sorts are other in the same category that works well on small number of elements.
If number of elements is large, Merge, Quick or Head sort are better

2. Bubble Sort
3. Merge Sort
4. Quick Sort

For small numbers of elements, a few sorting algorithms can be efficient due to their simplicity and low overhead. In addition to Insertion Sort, the following sorting techniques can be effective for small datasets:

1. **Selection Sort:** This algorithm works by repeatedly finding the minimum (or maximum) element from the unsorted part and swapping it with the first unsorted element. Its time complexity is \(O(n^2)\), but because of its simplicity, it can be efficient on small arrays.

2. **Bubble Sort:** In bubble sort, the list is traversed repeatedly, and adjacent elements are swapped if they are in the wrong order. The process is repeated until no swaps are needed. Like Selection Sort, its time complexity is \(O(n^2)\) for the average and worst-case scenarios, but it can be efficient for small lists, especially if they're mostly sorted.
After every pass the biggest element is in the end 

Total no. of passes: n-1 
// Outer loop for (i = 0; i < n-1; i++)

Total no. of comparisons: n*(n-1)/2 
// Inner loop: This does the actual comparisons and possible swaps. We subtract i because with every pass, the largest element bubbles up to the end, so we don't need to check the end anymore 
for (j = 0; j < n-1 -i; j++)
It can be optimized by stopping the algorithm if the inner loop didn’t cause any swap. 


3. **Shell Sort:** This is a generalization of Insertion Sort where you sort pairs of elements far apart from each other, gradually reducing the gap between elements being compared. With a good gap sequence, Shell Sort can be much faster than \(O(n^2)\), but for small lists, its main advantage is simplicity and the potential to be faster than simple Insertion Sort.

4. **Gnome Sort (or Stupid Sort):** This is a variation of Insertion Sort but even simpler in concept. It's not efficient for larger datasets, but for very small arrays, its simplicity can make it useful.

However, it's important to note that when the dataset is really small, the difference in absolute runtimes between these algorithms and more advanced algorithms like QuickSort or MergeSort might be negligible. In real-world applications, when sorting small datasets, the choice of algorithm might come down to other factors such as ease of implementation, familiarity, or the existing libraries available in a programming language.

For libraries and frameworks, they often switch to simpler algorithms like Insertion Sort when sorting smaller partitions or subsets of data because the overhead of more advanced algorithms isn't justified for small sizes. For example, some implementations of QuickSort might switch to Insertion Sort for small partitions.

*/

#include<stdio.h> // for printf
#include<stdbool.h>

#define MAX(a,b) \
  ((a<b)?a:b)

void print_array(int* in_arr, int len)
{
  printf("\nPrinting array of size:%d: ", len);
  for (int i=0; i<len; i++)
  {
    printf(" %d", in_arr[i]);
  }
}

/* INSERTION SORT - Insert at the right place
"Having sorted array A[1..j-1] we insert A[j] in proper place >> sorted array A[1..j]"
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
    printf("\n Swapping %d %d", *xp, *yp);
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
// Loop of one pass from low towards high
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

/* Uses 2 pointer */
int partition1(int arr[], int low, int high)
{
  int pivot = arr[high];
  int index = high;
  high--;
  while (low<high)
  {
    if(arr[high] >= pivot)
    {
      high--;
    }
    if(arr[low] <= pivot)
    {
      low++;
    }
    swap(&arr[high], &arr[low]);
    high--;
    low++;
  }
  high = MAX(high, low);
  swap(&arr[high],&arr[index]); 
  return high;  
}
 
void quickSort1(int arr[], int low, int high)
{
  if (low<high)
  {
    int pi = partition1(arr, low, high);

    printf("\nQuicksort low:%d partition:%d high:%d arr[low]:%d arr[partition]:%d arr[high]:%d",
      low, pi, high, arr[low], arr[pi], arr[high]);
    quickSort1(arr, low,pi-1);
    quickSort1(arr, pi+1, high);
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
         
        printf("\nQuicksort low:%d partition:%d high:%d arr[low]:%d arr[partition]:%d arr[high]:%d",
          low, pi, high, arr[low], arr[pi], arr[high]);
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

  quickSort1(in_arr, 0, len-1);
  print_array(in_arr, len);

  return 0;
}
