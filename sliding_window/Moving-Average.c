#include <stdio.h>
#include <stdlib.h>
// Function to compute moving average
// of previous K elements
float* ComputeMovingAverage(int arr[], int N, int K)
{
	int i;
	float sum = 0;
	float* result =(float*)malloc(sizeof(float)*(N-K+1));

	// Initial sum of K elements.
	for (i = 0; i < K; i++) {
		sum += arr[i];
	}
	result[0] = sum/K;
	// Compute MA from index K
	float avg;
	for (i = K; i < N; i++) {
		sum -= arr[i - K];
		sum += arr[i];
		avg = sum / K;
		result[i-K+1] = avg;
	}
	return result;
}

// Driver code
int main()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	int N = sizeof(arr) / sizeof(arr[0]);
	int K = 3;
	float* result = NULL;
	result = ComputeMovingAverage(arr, N, K);
	for (int i=0; i<N-K+1; i++)
	{
		printf("%f ", result[i]);
	}
	return 0;
}

