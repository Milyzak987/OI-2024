#include <iostream>
#include <vector>
using namespace std;

// Function to sort numbers by the current bit
void sortByBit(vector<int>& arr, int bit) {
    if (bit < 0 || arr.size() <= 1) return;

    // Partition the array into two groups based on the current bit
    vector<int> zeroGroup, oneGroup;
    for (int num : arr) {
        if ((num & (1 << bit)) == 0) {
            zeroGroup.push_back(num); // Bit is 0
        } else {
            oneGroup.push_back(num); // Bit is 1
        }
    }

    // Recursively sort both groups for the next less significant bit
    sortByBit(zeroGroup, bit - 1);
    sortByBit(oneGroup, bit - 1);

    // Merge the two groups back
    arr.clear();
    arr.insert(arr.end(), zeroGroup.begin(), zeroGroup.end());
    arr.insert(arr.end(), oneGroup.begin(), oneGroup.end());
}

// Main function to sort the array
void sortArray(vector<int>& arr) {
    if (arr.empty()) return;

    // Determine the maximum number of bits needed (based on the largest number)
    int maxNum = *max_element(arr.begin(), arr.end());
    int maxBit = 0;
    while ((1 << maxBit) <= maxNum) maxBit++;

    // Sort starting from the most significant bit
    sortByBit(arr, maxBit - 1);
}

// Driver function
int main() {
    vector<int> arr = {7, 2, 5, 3, 8, 1};

    cout << "Original Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    sortArray(arr);

    cout << "Sorted Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}