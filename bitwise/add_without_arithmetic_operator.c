/* Half adder logic */                                                                                                                           // C Program to add two numbers
// without using arithmetic operator
#include<stdio.h>

int Add(int x, int y)
{
	// Iterate till there is no carry 
	while (y != 0)
	{
		// carry now contains common 
		//set bits of x and y
		unsigned carry = x & y; 

		// Sum of bits of x and y where at 
		//least one of the bits is not set
		x = x ^ y; 

		// Carry is shifted by one so that adding
		// it to x gives the required sum
		y = carry << 1;
	}
	return x;
}

int main()
{
	printf("%d", Add(15, 32));
	return 0;
}

