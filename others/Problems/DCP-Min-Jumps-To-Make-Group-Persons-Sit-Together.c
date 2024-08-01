/*
Minimum jumps required to make a group of persons sit together

There are M people sitting in a row of N seats, where M < N. Your task is to redistribute people such that there are no gaps between any of them, while keeping overall movement to a minimum.

For example, suppose you are faced with an input of [0, 1, 1, 0, 1, 0, 0, 0, 1], where 0 represents an empty seat and 1 represents a person. In this case, one solution would be to place the person on the right in the fourth seat. We can consider the cost of a solution to be the sum of the absolute distance each person must move, so that the cost here would be five.

Given an input such as the one above, return the lowest possible cost of moving people to remove all gaps.

*/
#include <stdio.h>
#include <stdlib.h>

int minJumps(int seats[], int n) {
    int position[1000]; // Assuming a maximum of 1000 seats
    int count = 0;

    // Traverse the seats and store the positions of occupied seats
    for (int i = 0; i < n; i++) {
        if (seats[i] == 1) {
            position[count] = i;
            count++;
        }
    }

    // If there are no occupied seats or all seats are occupied, no jumps are needed
    if (count == 0 || count == n) {
        return 0;
    }

    // Calculate the median index
    int med_index = (count - 1) / 2;

    // Calculate the median position
    int med_val = position[med_index];

    int ans = 0;

    // Calculate the minimum jumps by summing the absolute distances to the median
    for (int i = 0; i < count; i++) {
        ans += abs(position[i] - med_val);
    }

    return ans;
}

int main() {
    // Example input: {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0}
    //int seats[] = {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0};
    int seats[] = {0, 1, 1, 0, 1, 0, 0, 0, 1};
    int n = sizeof(seats) / sizeof(seats[0]);

    // Calculate and print the minimum jumps
    printf("Minimum jumps required: %d\n", minJumps(seats, n));

    return 0;
}


