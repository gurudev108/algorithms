#include <stdio.h>
#include <math.h>

#define TARGET_FREQUENCY 1000.0   // This is the frequency we want our PLL to lock onto
#define REFERENCE_FREQUENCY 950.0 // This is our PLL's initial reference frequency
#define ADJUSTMENT_FACTOR 0.05    // This value determines the step size of frequency adjustments

double pll(double inputFrequency, double referenceFrequency, double adjustmentFactor) {
    double error;
    double outputFrequency = referenceFrequency;

    // We'll run the PLL loop for a set number of iterations for demonstration purposes
    for (int i = 0; i < 100; i++) {
        error = inputFrequency - outputFrequency;

        // Adjust the output frequency based on the error
        if (error > 0) {
            outputFrequency += adjustmentFactor;
        } else if (error < 0) {
            outputFrequency -= adjustmentFactor;
        }

        printf("Iteration %d: Output Frequency = %f\n", i+1, outputFrequency);
    }

    return outputFrequency;
}

int main() {
    printf("Starting PLL with Target Frequency: %f\n", TARGET_FREQUENCY);
    double lockedFrequency = pll(TARGET_FREQUENCY, REFERENCE_FREQUENCY, ADJUSTMENT_FACTOR);
    printf("Locked Frequency: %f\n", lockedFrequency);
    return 0;
}
