#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;

vector<int> tree[MAXN];
int euler[MAXN], start[MAXN], finish[MAXN];
int fenwick[MAXN];
int n, timer = 0;

// Fenwick Tree
void update(int idx, int val) {
    while (idx <= n) {
        fenwick[idx] += val;
        idx += idx & -idx;
    }
}

int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += fenwick[idx];
        idx -= idx & -idx;
    }
    return sum;
}

// DFS to create Euler Tour
void dfs(int node, int parent) {
    start[node] = ++timer;
    euler[timer] = node;
    for (int child : tree[node]) {
        if (child != parent) {
            dfs(child, node);
        }
    }
    finish[node] = timer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Input
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // Create Euler Tour
    dfs(1, -1);

    vector<int> result(n + 1, 0);

    // Process each node
    for (int i = 1; i <= n; i++) {
        int node = euler[i];
        // Count nodes with IDs smaller than the current node in its subtree
        result[node] = query(start[node] - 1);
        // Update Fenwick Tree for the current node
        update(start[node], 1);
    }

    // Output results
    for (int i = 1; i <= n; i++) {
        cout << result[i] << "\n";
    }

    return 0;
}