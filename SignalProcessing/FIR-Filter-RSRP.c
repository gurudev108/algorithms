/*
write a FIR filter to calculate the filtered RSRP based on instantaneous RSRP values. Current value depends on last 10 values with most recent values having the most weight

In this example, the FIR filter is implemented with a set of coefficients (fir_coefficients) representing the weights assigned to the last 10 RSRP values. The fir_filter function takes the instantaneous RSRP value as input, updates the delay line, and computes the filtered RSRP value based on the weighted sum of the delayed values.
*/

#include <stdio.h>

#define FILTER_ORDER 10

// FIR filter coefficients (weights)
double fir_coefficients[FILTER_ORDER] = {0.05, 0.07, 0.1, 0.12, 0.15, 0.18, 0.15, 0.12, 0.1, 0.07};

// Function to perform FIR filtering
double fir_filter(double *input) {
    static double delay_line[FILTER_ORDER] = {0}; // Delay line to store the last FILTER_ORDER values
    double output = 0;

    // Shift values in the delay line
    for (int i = FILTER_ORDER - 1; i > 0; --i) {
        delay_line[i] = delay_line[i - 1];
    }

    // Insert the most recent value at the beginning of the delay line
    delay_line[0] = *input;

    // Perform the FIR filtering
    for (int i = 0; i < FILTER_ORDER; ++i) {
        output += fir_coefficients[i] * delay_line[i];
    }

    return output;
}

int main() {
    // Simulate instantaneous RSRP values
    double rsrp_values[] = {-80.0, -78.0, -85.0, -82.0, -75.0, -73.0, -78.0, -80.0, -77.0, -79.0};

    // Number of samples
    int num_samples = sizeof(rsrp_values) / sizeof(rsrp_values[0]);

    // Calculate the filtered RSRP values
    printf("Instantaneous RSRP\tFiltered RSRP\n");
    for (int i = 0; i < num_samples; ++i) {
        double filtered_rsrp = fir_filter(&rsrp_values[i]);
        printf("%.2f\t\t\t%.2f\n", rsrp_values[i], filtered_rsrp);
    }

    return 0;
}

