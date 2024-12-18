#include <iostream>
#include <vector>
using namespace std;

void sortWithXOR(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    // Perform a bubble sort-like algorithm with XOR as the adjustment
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                // Apply XOR operations to make arr[i] <= arr[i + 1]
                arr[i] = arr[i] ^ arr[i + 1];
                arr[i + 1] = arr[i] ^ arr[i + 1];
                arr[i] = arr[i] ^ arr[i + 1];
                swapped = true;
            }
        }
    } while (swapped);
}

int main() {
    vector<int> arr = {7, 2, 5, 3, 8, 1};

    cout << "Original Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    sortWithXOR(arr);

    cout << "Sorted Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}