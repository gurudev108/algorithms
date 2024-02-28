/* This file contains my experiments with Stacks */


int push (int *A, int item)
{

  return 0;
}

int pop (int *A)
{

  return 0;
}

int isEmpty (int *A)
{
  return 0;
}

int isFull (int* A)
{
  return 0;
}

int peek (int* A)
{
  return 0;
}

/* 
Application: Time Series
The span s[i] of a stock's price on a certain day i is the max number of consecutive days
the price of the stock has been less than or equal to its price on day
Input n element array P of numbers such that P[i] is the price of stock on that day
Output am n element array S of numbers such that S[i] is the span of the stock on day i.
*/

 
int main()
{
  /* Stack using arrays */
  int A[10];
  int P[10] = {100,102,104,101,103, 106, 110, 120, 121,125};
  computeSpan(&P[0]);
  return 0;
}
