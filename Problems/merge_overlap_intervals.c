/*
Merge overlapping intervals
The goal of this exercise is to merge all the overlapping intervals of a given list to produce a list that has only mutually exclusive intervals.

Problem statement: You have an array (list) of interval pairs as input where each interval has a start and end timestamp, sorted by starting timestamps. Merge the overlapping intervals and return a new output array.

Consider an input array below. Intervals (1, 5), (3, 7), (4, 6), (6, 8) are overlapping so they should be merged to one interval (1, 8). Similarly, intervals (10, 12) and (12, 15) are also overlapping and should be merged to (10, 15).

https://www.educative.io/blog/apple-coding-interview-questions?eid=5082902844932096
*/

// C program to merge overlapping Intervals in
// O(n Log n) time and O(1) extra space.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // for qsort()

typedef struct Interval
{
  int start;
  int end;
} Interval;

int comp(const void* a, const void* b)
{
  return ((Interval *)a)->start - ((Interval *)b)->start;
}

int max (int a, int b)
{
  return (a>b)? a: b;
}

void merge_interval(Interval arr[], int n)
{
  qsort(arr, n, sizeof(arr[0]), comp);

  int index = 0;

  for (int i=1; i<n; i++)
  {
    if(arr[i].start <= arr[index].end)
    {
      arr[index].end = max(arr[index].end, arr[i].end);
    }
    else {
      index++;
      arr[index] = arr[i];
    }
  }

  // Print intervals
  printf("\nMerged Intervals: ");
  for (int i=0; i<= index; i++)
  {
    printf("(%d, %d)", arr[i].start, arr[i].end);
  }
}


//Driver function
int main()
{
  Interval arr[] = {{6,8}, {1,9}, {2,4}, {4,7}, {10,12}};
  int n = sizeof(arr)/sizeof(arr[0]);
  merge_interval(arr, n);
  return 0;
}
