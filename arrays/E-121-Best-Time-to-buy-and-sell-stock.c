/* 
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
121. Best Time to Buy and Sell Stock

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

*/

#include <stdio.h>
#include <limits.h>
int maxProfit(int* prices, int pricesSize){

  int min_price = INT_MAX;
  int max_profit = INT_MIN;
  for (int i=0; i<pricesSize; i++)
  {
    if(min_price > prices[i])
    {
      min_price = prices[i];
    }
    if (max_profit < prices[i] - min_price)
    {
      max_profit = prices[i] - min_price;
    }
  }
  
  return max_profit;
}
int main()
{
  int prices[] = {7,6,4,3,1};
  int result = maxProfit(prices, sizeof(prices)/sizeof(prices[0]));
  printf("result= %d", result);
  return 0; 
}
