/* C++ Reverse a binary number */

#include <iostream>
#include <vector>

using namespace std;

// helper method to show actual bits
void showBits(int n)
{
    vector<int> bits;
    for(int i = 0; i < sizeof(int) * 8; i++) 
    {
        if((n & 1) > 0) bits.push_back(1);
        else bits.push_back(0);
        n = n >> 1;
    }
    for(int i = bits.size()-1; i >= 0; i--) 
    {
        cout << bits[i] << ",";
    }
}

unsigned int reverseBits(unsigned int num)
{
  unsigned int rev = 0;
  while (num)
  {
    rev = rev<<1;
    rev |= num&1;
    num = num>>1;
  }
  return rev;

}

int main()
{
  unsigned int num = 11;
  unsigned int reverse = reverseBits(num);
  printf("\nReverse of %d is %d", num, reverse);
  printf("\nInput =");
  showBits(num);
  printf("\nOutput=");
  showBits(reverse);

  return 0;
}
