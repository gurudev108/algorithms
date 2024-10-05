#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to find the minimum number of columns to remove
int min_deletion_size(const vector<string>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int remove_count = 0;

    // Iterate through each column
    for (int col = 0; col < cols; ++col) {
        // Check if this column is lexicographically ordered
        bool ordered = true;
        for (int row = 1; row < rows; ++row) {
            if (matrix[row][col] < matrix[row - 1][col]) {
                // If any character is out of order, increment the count
                ordered = false;
                break;
            }
        }
        if (!ordered) {
            remove_count++;
        }
    }

    return remove_count;
}

int main() {
    // Example 1
    vector<string> matrix1 = {
        "cba",
        "daf",
        "ghi"
    };
    cout << "Columns to remove: " << min_deletion_size(matrix1) << endl;  // Output: 1

    // Example 2
    vector<string> matrix2 = {
        "abcdef"
    };
    cout << "Columns to remove: " << min_deletion_size(matrix2) << endl;  // Output: 0

    // Example 3
    vector<string> matrix3 = {
        "zyx",
        "wvu",
        "tsr"
    };
    cout << "Columns to remove: " << min_deletion_size(matrix3) << endl;  // Output: 3

    return 0;
}

