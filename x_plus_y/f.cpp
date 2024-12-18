#include <iostream>
#include <vector>
#include <deque>
using namespace std;

const int MAXN = 1007; // Maximum size of the array
vector<int> arr(MAXN); // Global array of size MAXN
deque<pair<int, int>> ans; // Global deque to store XOR operations

// Perform XOR swap for two consecutive indices and record the operation
void applyXOR(int i, int j) {
    arr[i] ^= arr[j];
    arr[j] ^= arr[i];
    arr[i] ^= arr[j];
    ans.emplace_back(i, j); // Record the XOR operation
}

// Bubble a value at `idx` to the correct position by swapping consecutive elements
void bubbleToPosition(int idx, int target) {
    while (idx > target) {
        applyXOR(idx - 1, idx);
        idx--;
    }
}

// Merge function: merge two sorted halves by swapping consecutive numbers
void merge(int left, int mid, int right) {
    vector<int> merged;
    int i = left, j = mid + 1;

    // Temporary array to store sorted elements
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            merged.push_back(arr[i++]);
        } else {
            merged.push_back(arr[j++]);
        }
    }

    // Add remaining elements from the left half
    while (i <= mid) {
        merged.push_back(arr[i++]);
    }

    // Add remaining elements from the right half
    while (j <= right) {
        merged.push_back(arr[j++]);
    }

    // Bubble elements back into the original array
    for (int k = 0; k < merged.size(); k++) {
        if (arr[left + k] != merged[k]) {
            // Bubble the correct value into position
            bubbleToPosition(left + k, left + k - 1);
            arr[left + k] = merged[k];
        }
    }
}

// Recursive merge sort function
void mergeSort(int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursively sort the left and right halves
    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    // Merge the sorted halves
    merge(left, mid, right);
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
    mergeSort(0, n - 1);

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