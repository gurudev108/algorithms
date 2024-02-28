/*
Parity of a number is used to define if the total number of set-bits(1-bit in binary representation) in a number is even or odd.
If the total number of set-bits in the binary representation of a number is even then the number is said to have even parity, otherwise, it will have odd parity.
*/

#include <stdio.h>
#include <stdbool.h>

int main()
{
  int number = 7;	 //7 means 111 in binary; 3 bits set = odd parity 
  bool oddParity = false;

  printf("Parity of %d is", number);	
  while(number) //while number != 0
  {
    //invert the parity because the next statement eliminates one 1
    oddParity = !oddParity;	 
		
    //eliminate one 1 from number
    number &= (number-1);	 
  }
  printf(" %d", oddParity);
  return 0;
}

