/*
write a similar program but with more complex feedback algorithms such as PID (Proportional-Integral-Derivative) control?

Certainly! Let’s move from simple proportional control to PID (Proportional-Integral-Derivative) control. PID control is a more advanced feedback mechanism that adjusts the control output based on three terms:
Proportional (P): Corrects the error in proportion to how far the system is from the target.
Integral (I): Accounts for the accumulation of past errors, helping to eliminate any residual steady-state error.
Derivative (D): Predicts future errors based on the current rate of change, dampening overshooting.
PID Control Overview:
Proportional term (P): Scales the error linearly.
Integral term (I): Sums the error over time, correcting persistent offsets.
Derivative term (D): Looks at the rate of change of the error, helping to smoothen out large changes.
Now let’s implement a PID-based control system to dynamically adjust the resistor value R1 to regulate the voltage at 3.3V.

Key Parameters:
KP, KI, KD: These are the proportional, integral, and derivative gains, respectively. They determine how aggressively the controller responds to the error, accumulated error, and predicted future error. You can fine-tune these to improve the performance of the PID controller.
Integral Sum: Accumulates over time, so persistent small errors will gradually influence the system more.
Derivative: Helps prevent overshooting by accounting for the rate of error change.


*/

#include <stdio.h>
#include <math.h>

#define TARGET_VOLTAGE 3.3   // Desired regulated voltage (V)
#define INPUT_VOLTAGE 12.0   // Input bus voltage (V)
#define INITIAL_RESISTANCE 1000.0  // Initial guess for R1 (Ohms)
#define TOLERANCE 0.001      // Tolerance for voltage regulation
#define MAX_ITERATIONS 500   // Maximum number of iterations

// PID controller constants
#define KP 1.0   // Proportional gain
#define KI 0.05  // Integral gain
#define KD 0.01  // Derivative gain

// Function to calculate the output voltage based on resistor values
double calculate_output_voltage(double input_voltage, double R1, double R2) {
    return (R2 / (R1 + R2)) * input_voltage;
}

// PID control function to adjust R1 to regulate the output voltage
double pid_control(double input_voltage, double target_voltage, double R1, double R2) {
    double output_voltage;
    double error, previous_error = 0;
    double integral = 0;
    double derivative;
    int iteration = 0;

    do {
        // Calculate current output voltage
        output_voltage = calculate_output_voltage(input_voltage, R1, R2);

        // Calculate the error (difference between target and actual voltage)
        error = target_voltage - output_voltage;

        // Accumulate the integral (sum of past errors)
        integral += error;

        // Calculate the derivative (rate of change of error)
        derivative = error - previous_error;

        // PID adjustment formula: adjust R1 based on P, I, D terms
        double adjustment = KP * error + KI * integral + KD * derivative;
        R1 -= adjustment;  // Decrease R1 if error is positive, increase if error is negative

        // Print the current state of the system
        printf("Iteration %d: R1 = %.2f Ohms, Output Voltage = %.4f V, Error = %.4f V\n", 
               iteration, R1, output_voltage, error);

        previous_error = error;
        iteration++;

        // Stop if error is within tolerance
    } while (fabs(error) > TOLERANCE && iteration < MAX_ITERATIONS);

    return R1;
}

int main() {
    double R1 = INITIAL_RESISTANCE; // Initial guess for R1
    double R2 = 1000.0;             // Fixed value of R2 (Ohms)

    printf("Starting PID-controlled feedback regulation to achieve %.2fV output from %.2fV input...\n", TARGET_VOLTAGE, INPUT_VOLTAGE);

    // Call PID control function to adjust R1 dynamically
    R1 = pid_control(INPUT_VOLTAGE, TARGET_VOLTAGE, R1, R2);

    printf("\nFinal Resistor Value: R1 = %.2f Ohms\n", R1);

    return 0;
}

