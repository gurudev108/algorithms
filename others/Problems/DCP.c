#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int minCost(int seats[], int n) {
    int numPeople = 0;
    int totalCost = 0;

    // Count the number of people
    for (int i = 0; i < n; ++i) {
        if (seats[i] == 1) {
            numPeople++;
        }
    }

    // If there are no people, the cost is 0
    if (numPeople == 0) {
        return 0;
    }

    // Create an array to store the indices of seats where people are sitting
    int *peopleIndices = (int *)malloc(numPeople * sizeof(int));
    int index = 0;

    // Populate the array with indices
    for (int i = 0; i < n; ++i) {
        if (seats[i] == 1) {
            peopleIndices[index++] = i;
        }
    }

    // Sort the array of indices
    qsort(peopleIndices, numPeople, sizeof(int), compare);

    // Calculate the median index
    int medianIndex = peopleIndices[numPeople / 2];

    printf("\n medianIndex =%d", medianIndex);

    // Calculate the cost by summing the absolute distances
    for (int i = 0; i < numPeople; ++i) {
        totalCost += abs(peopleIndices[i] - medianIndex);
    }

    free(peopleIndices);

    return totalCost;
}

int main() {
    // Example input: [0, 1, 1, 0, 1, 0, 0, 0, 1]
    int seats[] = {0, 1, 1, 0, 1, 0, 0, 0, 1};
    int n = sizeof(seats) / sizeof(seats[0]);

    int cost = minCost(seats, n);

    printf("The lowest possible cost of moving people is: %d\n", cost);

    return 0;
}
