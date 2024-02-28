#include <stdio.h>

unsigned int custom_divide(unsigned int dividend, unsigned int divisor) {
    if (divisor == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        return 0; // Handle division by zero error
    }

    unsigned int quotient = 0;
    unsigned int remainder = 0;

    // Perform binary division
    for (int i = 31; i >= 0; --i) {
        printf("\nLoop i=%d dividend=%d divisor=%d remainder=%d quotient=%d", i, dividend, divisor, remainder, quotient);
        remainder <<= 1;
        remainder |= (dividend >> i) & 1;

        if (remainder >= divisor) {
            remainder -= divisor;
            quotient |= 1 << i;
        }
    }

    return quotient;
}

int main() {
    unsigned int dividend = 42;
    unsigned int divisor = 3;

    unsigned int result = custom_divide(dividend, divisor);

    printf("%u divided by %u is %u\n", dividend, divisor, result);

    return 0;
}

