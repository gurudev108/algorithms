/*
Daily Coding Problem#593 Sunset View

You are given an array representing the heights of neighboring buildings on a city street, from east to west. The city assessor would like you to write an algorithm that returns how many of these buildings have a view of the setting sun, in order to properly value the street.

For example, given the array [3, 7, 8, 3, 6, 1], you should return 3, since the top floors of the buildings with heights 8, 6, and 1 all have an unobstructed view to the west.

Can you do this using just one forward pass through the array?

*/
#include <stdio.h>

int sunset_view(int* heights, int size)
{
  int max_so_far = 0;
  int count = 0;
  for (int i=size-1; i>=0; i--)
  {
    if (max_so_far < heights[i])
    {
      max_so_far = heights[i];
    }
    else
    {
      count++;
    }
  }
  return count;
}

int main()
{
  int heights[] = {3,7,8,3,6,1};
  int len = sizeof(heights)/sizeof(heights[0]);

  int result = sunset_view(heights, len);
  printf("Number of buildings with sunset view = %d", result);
  return 0;
}
