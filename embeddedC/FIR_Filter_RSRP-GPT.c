/*
Prompt:
write a FIR filter to calculate the filtered RSRP based on instantaneous RSRP values. 
Current value depends on last 10 values with most recent values having the most weight

Output:
Filtered RSRP value: -121.95
*/

#include <stdio.h>

#define FILTER_SIZE 10

// Function to calculate the filtered RSRP value
double fir_filter_rsrp(double rsrp_values[], int size) {
    // FIR filter coefficients (weights)
    double fir_coefficients[FILTER_SIZE] = {0.05, 0.05, 0.1, 0.1, 0.1, 0.15, 0.15, 0.2, 0.25, 0.25};
    double filtered_rsrp = 0.0;

    // Apply FIR filter: weighted sum of last 10 values
    for (int i = 0; i < FILTER_SIZE; i++) {
        filtered_rsrp += rsrp_values[size - FILTER_SIZE + i] * fir_coefficients[i];
    }

    return filtered_rsrp;
}

int main() {
    // Example array of RSRP values
    double rsrp_values[] = {-95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84};
    int size = sizeof(rsrp_values) / sizeof(rsrp_values[0]);

    // Calculate filtered RSRP value
    double filtered_value = fir_filter_rsrp(rsrp_values, size);

    // Print the result
    printf("Filtered RSRP value: %.2f\n", filtered_value);

    return 0;
}

