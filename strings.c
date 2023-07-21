/* Find a substring */

// Brute Force

/* Controlling Set - set of chars, set control a string if those chars appear in the string
Function - that will tell us the shortest substring controlled by the set 

Example - 
s = "helloworld"
set = {'l', 'r', 'w'}
This set controls the entire string. Find the shortest substring controlled by the set

Brute force = O(n^2) x O(n) = O(n^3)
- How many substrings of h = n, how many substring of e = n-1 so total O(n^2)
- Check which substring to pick


*/
