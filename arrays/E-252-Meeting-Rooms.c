/*
Leetcode Easy 252. Meeting rooms

Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.

Approach:
1. Sorting the Intervals:
First, sort the intervals based on their start times. This will help us easily check for overlaps by comparing each interval with the previous one.

2. Checking for Overlaps:
Iterate through the sorted intervals and check if the start time of the current interval is less than the end time of the previous interval. If this condition is met, it means there is an overlap, and the person cannot attend all meetings.

Output:
A person cannot attend all meetings
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

// Function to determine if a person can attend all meetings
int canAttendMeetings(struct Interval* intervals, int intervalsSize) {
    if (intervalsSize == 0) {
        return 1;
    }

    // Sort the intervals by start time
    qsort(intervals, intervalsSize, sizeof(struct Interval), compareStart);

    // Check for overlapping intervals
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i].start < intervals[i - 1].end) {
            return 0; // There is an overlap, so cannot attend all meetings
        }
    }

    return 1; // No overlap, so can attend all meetings
}

// Helper function to print the result (for testing)
void printResult(int result) {
    if (result) {
        printf("A person can attend all meetings.\n");
    } else {
        printf("A person cannot attend all meetings.\n");
    }
}

int main() {
    struct Interval intervals[] = {{0, 30}, {5, 10}, {15, 20}};
    int intervalsSize = sizeof(intervals) / sizeof(intervals[0]);

    int result = canAttendMeetings(intervals, intervalsSize);
    printResult(result);

    return 0;
}

