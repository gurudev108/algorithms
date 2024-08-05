/*
A Kalman filter is an algorithm that provides estimates of some unknown variables given a series of measurements observed over time. It is widely used in various fields, including control systems, navigation, signal processing, and finance, due to its efficiency and accuracy in estimating the state of a dynamic system
*/
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

/*
Explanation
Key Characteristics and Concepts
State Estimation:
The Kalman filter estimates the state of a system over time, even in the presence of noise and uncertainty. The state could include variables such as position, velocity, and acceleration in a tracking system.
Predict-Update Cycle:
The algorithm operates in two main steps:
Prediction Step: The filter uses a mathematical model of the system to predict the next state and its uncertainty based on the current state estimate and the process model.
Update Step: The filter adjusts the predicted state estimate using new measurements and their associated uncertainties, improving the accuracy of the estimate.
Linear Gaussian Systems:
The Kalman filter is optimal for linear systems where the process and measurement noise are Gaussian. The state transition and measurement processes are assumed to be linear with additive Gaussian noise.
Recursive Nature:
The Kalman filter is recursive, meaning it does not require the complete history of measurements to be kept and reprocessed. It updates the state estimate and error covariance matrix incrementally as new measurements arrive.
*/