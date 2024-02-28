/*
Given two 16–bit positive values stored in 32–bit integer variables, find the product using the 8–bit multiply operator 
that takes two 8–bit numbers and returns a 16–bit value.

The idea is to divide the given 16–bit numbers (say m and n) into 8–bit numbers first (say mLow, mHigh and nLow, nHigh). 
Now the problem is reduced to something similar to the multiplication of a 2–digit number with another 2–digit number. 
For example,


                                   [mHigh mLow]    ×
                                   [nHigh nLow]
                                   – – – – – – –
                    [mHigh * nLow] [mLow * nLow]
    [mHigh * nHigh] [mLow * nHigh]
– – – – – – – – – – – – – – – – – – – – – – – – – – – – – – – –
[mHigh * nHigh] + [mLow * nHigh + mHigh * nLow] + [mLow * nLow]
– – – – – – – – – – – – – – – – – – – – – – – – – – – – – – – –
*/

#include <stdint.h>
#include <stdio.h>
uint32_t multiply16bit (uint16_t m, uint16_t n)
{
  uint8_t mLow = (m & 0x00FF);
  uint8_t mHigh = (m & 0xFF00)>>8;
  uint8_t nLow = (n & 0x00FF);
  uint8_t nHigh = (n & 0xFF00)>>8;

  uint16_t mLow_nLow = mLow * nLow;
  uint16_t mHigh_nLow = mHigh * nLow;
  uint16_t mLow_nHigh = mLow * nHigh;
  uint16_t mHigh_nHigh = mHigh * nHigh;

  return mLow_nLow + ((mHigh_nLow + mLow_nHigh)<<8) + (mHigh_nHigh<<16);
}

int main()
{
  uint16_t num1 = 23472;
  uint16_t num2 = 2600;
  printf("\nNormal multiply %d", num1*num2);
  printf("\nUsing 8bit multiplier %d", multiply16bit(num1, num2));

  return 0; 
}
