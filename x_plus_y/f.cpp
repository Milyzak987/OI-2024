#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Global variables
vector<unordered_map<int, int>> tree;
int n;

// Function to build the segment tree
void build(vector<int>& arr, int v, int tl, int tr) {
    if (tl == tr) {
        tree[v][arr[tl]]++;
    } else {
        int tm = (tl + tr) / 2;
        build(arr, v * 2, tl, tm);
        build(arr, v * 2 + 1, tm + 1, tr);
        for (const auto& [key, value] : tree[v * 2]) {
            tree[v][key] += value;
        }
        for (const auto& [key, value] : tree[v * 2 + 1]) {
            tree[v][key] += value;
        }
    }
}

// Function to update the segment tree
void update(int v, int tl, int tr, int pos, int oldVal, int newVal) {
    // Update the current node
    tree[v][oldVal]--;
    if (tree[v][oldVal] == 0) {
        tree[v].erase(oldVal);
    }
    tree[v][newVal]++;
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            update(v * 2, tl, tm, pos, oldVal, newVal);
        } else {
            update(v * 2 + 1, tm + 1, tr, pos, oldVal, newVal);
        }
    }
}

// Function to query the segment tree
int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r) return 0;
    if (l == tl && r == tr) {
        return tree[v].count(x) ? tree[v][x] : 0;
    }
    int tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, min(r, tm), x) +
           query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
}

int main() {
    vector<int> arr = {1, 2, 1, 3, 2, 1};
    n = arr.size();
    tree.resize(4 * n);

    // Build the segment tree
    build(arr, 1, 0, n - 1);

    // Example queries and updates
    cout << query(1, 0, n - 1, 0, 5, 1) << endl; // Count of "1" in the range [0, 5]
    update(1, 0, n - 1, 2, 1, 4);               // Change arr[2] from 1 to 4
    cout << query(1, 0, n - 1, 0, 5, 1) << endl; // Count of "1" in the range [0, 5] after update
    cout << query(1, 0, n - 1, 1, 3, 2) << endl; // Count of "2" in the range [1, 3]
}