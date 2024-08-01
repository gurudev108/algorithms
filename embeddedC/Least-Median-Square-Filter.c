#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// LMS filter parameters
#define MU 0.01 // Step size or learning rate

// Function to perform LMS adaptive filtering
void lms_filter(double *input, double *desired, double *weights, int num_samples) {
    for (int i = 0; i < num_samples; ++i) {
        // Filter output
        double output = weights[0] * input[i];

        // Update weights (Least Mean Squares update rule)
        for (int j = 0; j < 1; ++j) {
            weights[j] = weights[j] + MU * (desired[i] - output) * input[i];
        }
    }
}

int main() {
    // Simulate input signal and desired signal
    double input[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double desired[] = {2.0, 4.0, 6.0, 8.0, 10.0};

    // Initialize weights
    double weights[1] = {1.0};

    // Number of samples
    int num_samples = sizeof(input) / sizeof(input[0]);

    // Perform LMS filtering
    lms_filter(input, desired, weights, num_samples);

    // Display the resulting weights
    printf("Estimated Weight: %.4f\n", weights[0]);

    return 0;
}

