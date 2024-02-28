#include <stdio.h>

int main() {
    double  a = 0, b = 1, sum_even = 0, temp;

    while (a <= 10000) {
        if (a % 2 == 0) {
            sum_even += a;
        }

        // Generate the next Fibonacci number
        temp = a;
        a = b;
        b = temp + b;
    }

    printf("Sum of even Fibonacci numbers up to 10,000: %lu\n", sum_even);
    return 0;
}

