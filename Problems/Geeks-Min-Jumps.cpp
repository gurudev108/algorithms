// C++ Program to find the minimum
// number of jumps required to
// group all ones together in
// the binary string
//#include <string>
#include <iostream>

using namespace std;

// Function to get the
// minimum jump value
int getMinJumps(string s)
{
	// Store all indices
	// of ones
	vector<int> ones;

	int jumps = 0, median = 0, ind = 0;

	// Populating one's indices
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '1')
			ones.push_back(i);
	}

	if (ones.size() == 0)
		return jumps;

	// Calculate median
	median = ones[ones.size() / 2];
	ind = median;
	cout << "median="<<ind<<endl;

	// Jumps required for 1's
	// to the left of median
	for (int i = ind; i >= 0; i--) {
		if (s[i] == '1') {
			jumps += ind - i;
			ind--;
		}
	}
	cout << "jumps required on left of median ="<<jumps <<endl;
	ind = median;

	// Jumps required for 1's
	// to the right of median
	for (int i = ind; i < s.length(); i++) {
		if (s[i] == '1') {
			jumps += i - ind;
			ind++;
		}
	}
	cout << "jumps on right of median="<<jumps<<endl;

	// Return the final answer
	return jumps;
}

// Driver Code
int main()
{
	string S = "011010001";
	cout << getMinJumps(S) << '\n';
	return 0;
}

