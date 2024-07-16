/*
Leetcode Medium 253. Meeting Rooms II
Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

Approach-
Use qsort for start times 
Use qsort as a workaround for min heap for end times.

Output:
Minimum number of conference rooms required: 2

*/

#include <stdio.h>
#include <stdlib.h>

// Definition for an interval
struct Interval {
    int start;
    int end;
};

// Comparator function for qsort to sort intervals by start time
int compareStart(const void* a, const void* b) {
    return ((struct Interval*)a)->start - ((struct Interval*)b)->start;
}

// Comparator function for qsort to sort end times
int compareEnd(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// Function to find the minimum number of conference rooms required
int minMeetingRooms(struct Interval* intervals, int intervalsSize) {
    if (intervalsSize == 0) {
        return 0;
    }

    // Sort the intervals by start time
    qsort(intervals, intervalsSize, sizeof(struct Interval), compareStart);

    // Create an array to store the end times of ongoing meetings
    int* endTimes = (int*)malloc(intervalsSize * sizeof(int));
    int endTimesSize = 0;

    // Iterate through each interval
    for (int i = 0; i < intervalsSize; i++) {
        // If the current meeting can use an existing room, update the end time
        if (endTimesSize > 0 && endTimes[0] <= intervals[i].start) {
            endTimes[0] = intervals[i].end;
            // Re-sort the endTimes array to maintain order
            qsort(endTimes, endTimesSize, sizeof(int), compareEnd);
        } else {
            // Otherwise, allocate a new room
            endTimes[endTimesSize++] = intervals[i].end;
            qsort(endTimes, endTimesSize, sizeof(int), compareEnd);
        }
    }

    // The size of endTimes array is the number of conference rooms needed
    int result = endTimesSize;
    free(endTimes);
    return result;
}

// Helper function to print the result (for testing)
void printResult(int result) {
    printf("Minimum number of conference rooms required: %d\n", result);
}

int main() {
    struct Interval intervals[] = {{0, 30}, {5, 10}, {15, 20}};
    int intervalsSize = sizeof(intervals) / sizeof(intervals[0]);

    int result = minMeetingRooms(intervals, intervalsSize);
    printResult(result);

    return 0;
}

