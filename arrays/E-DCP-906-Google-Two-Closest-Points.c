/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given a set of points (x, y) on a 2D cartesian plane, find the two closest points. For example, given the points [(1, 1), (-1, -1), (3, 4), (6, 1), (-1, -6), (-4, -3)], return [(-1, -1), (1, 1)].

Verified Output:
The closest points are: (1, 1) and (-1, -1)
*/

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

typedef struct Point
{
  int x;
  int y;
} Point;

int distance(Point a, Point b)
{
  return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

int findClosestPoints(Point points[], int n, Point *closest1, Point *closest2)
{
  int minDistance = INT_MAX;
  int dist = 0;

  for (int i=0; i<n; i++)
  {
    for (int j=i+1; j<n; j++)
    {
      int dist = distance(points[i], points[j]);
    
      if (dist<minDistance)
      {
        minDistance = dist;
        *closest1 = points[i];
        *closest2 = points[j];
      }
    }
  }
  return minDistance;
}

int main()
{
  Point points[] = { {1,1}, {-1, -1}, {3,4}, {6,1}, {-1,-6}, {-4, -3}};
  int n = sizeof(points)/sizeof(points[0]);

  Point closest1, closest2;
  int result = findClosestPoints(points, n, &closest1, &closest2);

  printf("The closest points are: (%d, %d) and (%d, %d)\n", closest1.x, closest1.y, closest2.x, closest2.y);

  return 0;
}
