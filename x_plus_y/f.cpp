#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Drzewo przedziałowe z mapami do obsługi częstotliwości wartości
class SegmentTree {
private:
    vector<map<int, int>> tree;
    int n;

    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            tree[node][arr[start]]++;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, arr);
            build(2 * node + 1, mid + 1, end, arr);
            merge(tree[node], tree[2 * node], tree[2 * node + 1]);
        }
    }

    void merge(map<int, int>& parent, const map<int, int>& left, const map<int, int>& right) {
        parent = left;
        for (const auto& [key, val] : right) {
            parent[key] += val;
        }
    }

    void update(int node, int start, int end, int idx, int old_val, int new_val) {
        if (start == end) {
            tree[node][old_val]--;
            if (tree[node][old_val] == 0) tree[node].erase(old_val);
            tree[node][new_val]++;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, old_val, new_val);
            else
                update(2 * node + 1, mid + 1, end, idx, old_val, new_val);
            tree[node].clear();
            merge(tree[node], tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int node, int start, int end, int L, int R, int x) {
        if (R < start || end < L) return 0;
        if (L <= start && end <= R) {
            return tree[node].count(x) ? tree[node][x] : 0;
        }
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, L, R, x) +
               query(2 * node + 1, mid + 1, end, L, R, x);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    void update(int idx, int old_val, int new_val) {
        update(1, 0, n - 1, idx, old_val, new_val);
    }

    int query(int L, int R, int x) {
        return query(1, 0, n - 1, L, R, x);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    while (q--) {
        char type;
        cin >> type;
        if (type == '?') {
            int l, r, x;
            cin >> l >> r >> x;
            cout << segTree.query(l - 1, r - 1, x) << endl;
        } else if (type == '!') {
            int idx, x;
            cin >> idx >> x;
            idx--; // Przejście na indeksowanie od 0
            segTree.update(idx, arr[idx], x);
            arr[idx] = x;
        }
    }

    return 0;
}