/*
2's compliment

If you take the two's complement of a positive number, you get the negative representation of that number, 
and vice versa. If you take the two's complement of 5 ( 0101 ), you get 1011 which is how you represent -5 . 
If you take the two's complement of -5 ( 1011 ), you get 0101 , which is 5 

Output:
The 2's complement of 5 is -5
*/

#include <stdio.h>

// Function to calculate 2's complement of an integer
int twoComplement(int num) {
    // Calculate the number of bits in the integer
    int numBits = sizeof(num) * 8;
    
    // Calculate the 1's complement
    int onesComplement = ~num;
    
    // Add 1 to get the 2's complement
    int twosComplement = onesComplement + 1;
    
    return twosComplement;
}

int main() {
    int num = 5;
    
    // Calculate 2's complement of the number
    int result = twoComplement(num);
    
    printf("The 2's complement of %d is %d\n", num, result);
    
    return 0;
}

