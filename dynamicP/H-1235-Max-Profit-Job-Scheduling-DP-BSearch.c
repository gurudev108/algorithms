/*

Leetcode H 1235 Max Profit in Job Scheduling
Also see Heaps implementation 

Approach:
To solve the problem of finding the maximum profit in job scheduling without overlapping, we can use a dynamic programming approach with binary search. The key idea is to sort the jobs by their end times and then use a combination of dynamic programming and binary search to find the maximum profit that can be obtained.

Dynamic Programming with Binary Search
Approach:

Sort Jobs: Sort the jobs by their end times.
DP Array: Use a dynamic programming array dp where dp[i] represents the maximum profit up to the i-th job.
Binary Search: For each job, use binary search to find the last job that doesn't conflict (i.e., the job with the largest end time less than or equal to the current job's start time).
State Transition: Update the DP array based on whether you take the current job or not.

Output:
Maximum Profit: 250
*/
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
typedef struct Job {
    int startTime;
    int endTime;
    int profit;
} Job;

// Comparison function to sort jobs by endTime
int compare(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    return jobA->endTime - jobB->endTime;
}

// Binary search to find the last non-conflicting job
int findLastNonConflictingJob(Job jobs[], int n) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (jobs[mid].endTime <= jobs[n].startTime) {
            if (jobs[mid + 1].endTime <= jobs[n].startTime) {
                low = mid + 1;
            } else {
                return mid;
            }
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Function to find the maximum profit
int maxProfit(Job jobs[], int n) {
    // Sort jobs according to their end times
    qsort(jobs, n, sizeof(Job), compare);

    // Create an array to store the maximum profit until each job
    int *dp = (int *)malloc(n * sizeof(int));

    // Initialize dp array
    dp[0] = jobs[0].profit;

    // Fill dp array
    for (int i = 1; i < n; i++) {
        // Include the current job
        int profitIncludingCurrentJob = jobs[i].profit;

        // Find the last non-conflicting job
        int lastNonConflictingJob = findLastNonConflictingJob(jobs, i);
        if (lastNonConflictingJob != -1) {
            profitIncludingCurrentJob += dp[lastNonConflictingJob];
        }

        // Find the maximum profit
        dp[i] = (profitIncludingCurrentJob > dp[i - 1]) ? profitIncludingCurrentJob : dp[i - 1];
    }

    int maxProfit = dp[n - 1];
    free(dp);  // Free allocated memory
    return maxProfit;
}

int main() {
    // Example usage
    Job jobs[] = {{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}};
    int n = sizeof(jobs) / sizeof(jobs[0]);

    printf("Maximum Profit: %d\n", maxProfit(jobs, n));

    return 0;
}

/*
Sorting Jobs:
The jobs are sorted by their endTime using the qsort function. This helps in finding the last non-conflicting job more efficiently.

Binary Search:
The findLastNonConflictingJob function uses binary search to find the last job that does not conflict with the current job. It looks for the last job that ends before or when the current job starts.

Dynamic Programming Array:
The dp array stores the maximum profit that can be obtained up to each job. It is initialized with the profit of the first job.
For each job, we calculate the profit if we include the current job, considering the maximum profit from the last non-conflicting job.
We then update the dp array with the maximum of including the current job or excluding it.

Result:
The last element of the dp array contains the maximum profit that can be obtained without overlapping jobs.
Complexity
Time Complexity: O(nlogn)
O(nlogn) for sorting the jobs, and 
O(nlogn) for finding the last non-conflicting job using binary search, leading to an overall time complexity of 

O(nlogn).
Space Complexity:
O(n) for storing the dp array.
*/
