/*
Leetcode 278 First Bad Version

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

Approach:
1. Binary Search II
   1.1 while (left<right) - this was correct
   1.2 right = mid and not mid-1
   1.3 return left and not mid

Output:

Verified on Leetcode 18-10
*/

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    int mid = 1;
    
    while (left<right)
    {
        mid = left + (right - left)/2;
        if (isBadVersion(mid))
        {
            // @TODO right = mid -1 was incorrect
            right = mid;
        }
        else
        {
            left = mid +1;
        }
    }
    // @TODO return left and not mid
    return left;
    
}
