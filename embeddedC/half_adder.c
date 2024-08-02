/*
Digital Logic Background:
Half Adder: A half adder is a digital circuit that adds two single-bit binary numbers. It provides two outputs: the sum and the carry. The logic equations are:
Sum: Sum = A ⊕ B
Sum=A⊕B (XOR gate)
Carry: Carry = A & B
Carry=A&B (AND gate)

Explanation
Half Adder: The program computes the sum and carry for two single-bit inputs using XOR and AND operations, respectively.
Full Adder: The program computes the sum and carry-out for two single-bit inputs and a carry-in using the half adder logic and OR operation to combine carry results.

Output:
Enter two bits (0 or 1): 1
1
Half Adder Results:
Sum: 0
Carry: 1

*/
#include <stdio.h>

// Function to perform half adder logic
void halfAdder(int A, int B, int *sum, int *carry) {
    *sum = A ^ B;      // Sum = A XOR B
    *carry = A & B;    // Carry = A AND B
}

int main() {
    int A, B, sum, carry;

    printf("Enter two bits (0 or 1): ");
    scanf("%d %d", &A, &B);

    if ((A != 0 && A != 1) || (B != 0 && B != 1)) {
        printf("Invalid input! Please enter only 0 or 1.\n");
        return 1;
    }

    halfAdder(A, B, &sum, &carry);
    printf("Half Adder Results:\n");
    printf("Sum: %d\n", sum);
    printf("Carry: %d\n", carry);

    return 0;
}

