#include <stdio.h>

// Kalman filter parameters
double Q = 1e-4; // Process noise covariance
double R = 0.1; // Measurement noise covariance
double x_hat = 0; // Initial estimate
double P = 1; // Initial estimate error covariance
double K; // Kalman gain

// Function to perform Kalman filtering
double kalman_filter(double z) {
    // Prediction
    double x_hat_minus = x_hat;
    double P_minus = P + Q;

    // Update (correction)
    K = P_minus / (P_minus + R);
    x_hat = x_hat_minus + K * (z - x_hat_minus);
    P = (1 - K) * P_minus;

    return x_hat;
}

int main() {
    // Simulate measurements
    double measurements[] = {1.2, 1.4, 1.7, 1.5, 1.9};

    // Perform Kalman filtering
    int num_measurements = sizeof(measurements) / sizeof(measurements[0]);
    for (int i = 0; i < num_measurements; ++i) {
        double estimated_value = kalman_filter(measurements[i]);
        printf("Measurement: %.2f, Estimated Value: %.4f\n", measurements[i], estimated_value);
    }

    return 0;
}

