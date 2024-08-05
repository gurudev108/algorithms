/*

The LeetCode problem 621, "Task Scheduler," can be approached by calculating the most frequent task's frequency and determining the minimum intervals needed to separate these tasks by at least n intervals. The challenge lies in filling the intervals between the same tasks with other tasks or idle slots.

Problem Breakdown and Approach
Count the Frequency of Each Task:
Use an array to count the occurrences of each task.

Determine the Most Frequent Task:
Identify the task(s) with the highest frequency. The task with the maximum frequency will determine the minimum structure of the schedule.

Calculate the Idle Slots:
Calculate the minimum idle slots required by arranging the most frequent tasks and separating them with at least n intervals.

Fill the Idle Slots:
Use the remaining tasks to fill in the idle slots. If the idle slots are more than the number of remaining tasks, they stay as idle slots; otherwise, they get filled.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leastInterval(char* tasks, int tasksSize, int n) {
    int task_counts[26] = {0}; // Frequency array for each task (A-Z)

    // Count the frequency of each task
    for (int i = 0; i < tasksSize; i++) {
        task_counts[tasks[i] - 'A']++;
    }

    // Find the maximum frequency and count how many tasks have that maximum frequency
    int max_freq = 0;
    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (task_counts[i] > max_freq) {
            max_freq = task_counts[i];
            max_count = 1;
        } else if (task_counts[i] == max_freq) {
            max_count++;
        }
    }

    // Calculate the minimum intervals needed
    int part_count = max_freq - 1;
    int part_length = n - (max_count - 1);
    int empty_slots = part_count * part_length;
    int available_tasks = tasksSize - max_freq * max_count;
    int idles = empty_slots > available_tasks ? empty_slots - available_tasks : 0;

    return tasksSize + idles;
}

int main() {
    char tasks[] = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n = 2;
    int tasksSize = sizeof(tasks) / sizeof(tasks[0]);

    int result = leastInterval(tasks, tasksSize, n);
    printf("Minimum number of intervals required: %d\n", result);

    return 0;
}

