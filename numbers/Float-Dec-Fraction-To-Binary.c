/*
float to binary
Decimal fraction to binary

Output:
The binary representation of 10.625 is 1010.101
*/
#include <stdio.h>
#include <math.h>

// Function to convert the integer part of a float to binary
void intToBin(int num, char* binStr) {
    int i = 0;
    if (num == 0) {
        binStr[i++] = '0';
    }
    else {
        while (num > 0) {
            binStr[i++] = (num % 2) ? '1' : '0';
            num /= 2;
        }
    }
    binStr[i] = '\0';
    
    // Reverse the binary string
    for (int j = 0; j < i / 2; j++) {
        char temp = binStr[j];
        binStr[j] = binStr[i - j - 1];
        binStr[i - j - 1] = temp;
    }
}

// Function to convert the fractional part of a float to binary
void fracToBin(float frac, char* binStr) {
    int i = 0;
    while (frac > 0 && i < 23) { // Limit to 23 bits for precision
        frac *= 2;
        int bit = (int)frac;
        binStr[i++] = bit ? '1' : '0';
        frac -= bit;
    }
    binStr[i] = '\0';
}

// Function to convert a float to binary representation
void floatToBin(float num, char* binStr) {
    int intPart = (int)num;
    float fracPart = num - intPart;
    
    // Convert integer part
    char intBin[32] = {0}; // Buffer for integer binary part
    intToBin(intPart, intBin);
    
    // Convert fractional part
    char fracBin[24] = {0}; // Buffer for fractional binary part
    fracToBin(fracPart, fracBin);
    
    // Combine integer and fractional parts
    if (intPart == 0) {
        sprintf(binStr, "0.%s", fracBin);
    } else {
        sprintf(binStr, "%s.%s", intBin, fracBin);
    }
}

int main() {
    float num = 10.625;
    char binaryStr[64]; // Buffer for binary representation
    
    floatToBin(num, binaryStr);
    printf("The binary representation of %.3f is %s\n", num, binaryStr);
    
    return 0;
}

