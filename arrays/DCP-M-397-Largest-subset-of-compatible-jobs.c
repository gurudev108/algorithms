/*

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Job;

// Comparison function to sort jobs by their end time
int compare(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    return (jobA->end - jobB->end);
}

void find_largest_subset_of_compatible_jobs(Job jobs[], int n) {
    // Sort jobs by their end time
    qsort(jobs, n, sizeof(Job), compare);

    // Array to hold the indices of the selected jobs
    int selectedJobs[n];
    int count = 0;

    // The end time of the last selected job
    int last_end_time = -1;

    // Iterate through the sorted jobs
    for (int i = 0; i < n; i++) {
        if (jobs[i].start >= last_end_time) {
            // Select this job
            selectedJobs[count++] = i;
            last_end_time = jobs[i].end;
        }
    }

    // Print the selected jobs
    printf("The largest subset of compatible jobs is:\n");
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", jobs[selectedJobs[i]].start, jobs[selectedJobs[i]].end);
    }
}

int main() {
    Job jobs[] = {
        {0, 6},
        {1, 4},
        {3, 5},
        {3, 8},
        {4, 7},
        {5, 9},
        {6, 10},
        {8, 11}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    find_largest_subset_of_compatible_jobs(jobs, n);

    return 0;
}

