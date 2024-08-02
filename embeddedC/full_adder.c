/*

Full Adder: A full adder adds three single-bit binary numbers: two significant bits and an incoming carry. It provides a sum and a carry output. The logic equations are:
Sum: Sum=A⊕B⊕CarryIn
Sum=A⊕B⊕CarryIn
Carry: CarryOut=(A&B)∨(B&CarryIn)∨(A&CarryIn)
CarryOut=(A&B)∨(B&CarryIn)∨(A&CarryIn)

Full Adder: The program computes the sum and carry-out for two single-bit inputs and a carry-in using the half adder logic and OR operation to combine carry results.

Output:
Enter two bits (0 or 1) and carry-in bit (0 or 1): 1
1
1
Full Adder Results:
Sum: 1
Carry Out: 1
*/

#include <stdio.h>

// Function to perform full adder logic
void fullAdder(int A, int B, int CarryIn, int *sum, int *carryOut) {
    int sum1, carry1, carry2;

    // First half adder
    sum1 = A ^ B;       // Sum without carry
    carry1 = A & B;     // Carry from first half adder

    // Second half adder
    *sum = sum1 ^ CarryIn;   // Final sum
    carry2 = sum1 & CarryIn; // Carry from second half adder

    // Final carry out
    *carryOut = carry1 | carry2;
}

int main() {
    int A, B, CarryIn, sum, carryOut;

    printf("Enter two bits (0 or 1) and carry-in bit (0 or 1): ");
    scanf("%d %d %d", &A, &B, &CarryIn);

    if ((A != 0 && A != 1) || (B != 0 && B != 1) || (CarryIn != 0 && CarryIn != 1)) {
        printf("Invalid input! Please enter only 0 or 1.\n");
        return 1;
    }

    fullAdder(A, B, CarryIn, &sum, &carryOut);
    printf("Full Adder Results:\n");
    printf("Sum: %d\n", sum);
    printf("Carry Out: %d\n", carryOut);

    return 0;
}

