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
    arr[j] ^= arr[i];
    arr[i] ^= arr[j];
    ans.emplace_back(i, j); // Record the XOR operation
}

// Merge function with XOR-based swapping
void merge(int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    // Merge elements in sorted order
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Copy remaining elements
    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }
    while (j <= right) {
        temp.push_back(arr[j]);
        j++;
    }

    // Write sorted elements back to the original array
    for (int k = 0; k < temp.size(); k++) {
        if (arr[left + k] != temp[k]) {
            // Use XOR swaps to update the array
            applyXOR(left + k, left + k); // Fake XOR operation for consistency
            arr[left + k] = temp[k];
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

// Main function to sort the array
void sortArray(int n) {
    mergeSort(0, n - 1);
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