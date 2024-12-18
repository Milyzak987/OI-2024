#include <iostream>
#include <vector>
#include <deque>
using namespace std;

const int MAXN = 1007; // Maximum size of the array
vector<int> arr(MAXN); // Global array of size MAXN
deque<pair<int, int>> ans; // Global deque to store XOR operations

// Perform XOR operation and record it in the deque
void applyXOR(int i, int j) {
    arr[i] ^= arr[j];
    ans.emplace_back(i, j); // Record the XOR operation
}

// Function to sort numbers by the current bit
void sortByBit(int left, int right, int bit) {
    if (bit < 0 || left >= right) return;

    int mid = left; // Partition index

    // Partition the array into two groups based on the current bit
    for (int i = left; i <= right; i++) {
        if ((arr[i] & (1 << bit)) == 0) {
            swap(arr[mid], arr[i]); // Swap to group zeros to the left
            mid++;
        }
    }

    // Recursively sort both groups for the next less significant bit
    sortByBit(left, mid - 1, bit - 1);
    sortByBit(mid, right, bit - 1);
}

// Main function to sort the array
void sortArray(int n) {
    // Determine the maximum number of bits needed (based on the largest number)
    int maxNum = 0;
    for (int i = 0; i < n; i++) maxNum = max(maxNum, arr[i]);
    int maxBit = 0;
    while ((1 << maxBit) <= maxNum) maxBit++;

    // Sort starting from the most significant bit
    sortByBit(0, n - 1, maxBit - 1);
}

// Driver function
int main() {
    int n; // Size of the input array
    cout << "Enter the number of elements (<= 1007): ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // Sort the array
    sortArray(n);

    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // Output the XOR operations
    cout << "XOR Operations:" << endl;
    for (auto [i, j] : ans) {
        cout << "XOR applied between indices " << i << " and " << j << endl;
    }

    return 0;
}