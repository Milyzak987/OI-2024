#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class SegmentTree {
    vector<unordered_map<int, int>> tree;
    int n;

    void build(vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v][arr[tl]]++;
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            merge(tree[v * 2], tree[v * 2 + 1], tree[v]);
        }
    }

    void update(int v, int tl, int tr, int pos, int oldVal, int newVal) {
        tree[v][oldVal]--;
        if (tree[v][oldVal] == 0) {
            tree[v].erase(oldVal);
        }
        tree[v][newVal]++;
        if (tl != tr) {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, oldVal, newVal);
            else
                update(v * 2 + 1, tm + 1, tr, pos, oldVal, newVal);
        }
    }

    int query(int v, int tl, int tr, int l, int r, int x) {
        if (l > r) return 0;
        if (l == tl && r == tr) {
            return tree[v].count(x) ? tree[v][x] : 0;
        }
        int tm = (tl + tr) / 2;
        return query(v * 2, tl, tm, l, min(r, tm), x) +
               query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
    }

    void merge(const unordered_map<int, int>& left, const unordered_map<int, int>& right, unordered_map<int, int>& result) {
        result = left;
        for (const auto& [key, value] : right) {
            result[key] += value;
        }
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void update(int pos, int oldVal, int newVal) {
        update(1, 0, n - 1, pos, oldVal, newVal);
    }

    int query(int l, int r, int x) {
        return query(1, 0, n - 1, l, r, x);
    }
};

int main() {
    vector<int> arr = {1, 2, 1, 3, 2, 1};
    SegmentTree st(arr);

    // Przykładowe zapytania
    cout << st.query(0, 5, 1) << endl; // Liczba "1" w całym przedziale
    st.update(2, 1, 4);                // Zmieniamy arr[2] z 1 na 4
    cout << st.query(0, 5, 1) << endl; // Liczba "1" w całym przedziale po zmianie
    cout << st.query(1, 3, 2) << endl; // Liczba "2" w przedziale [1, 3]
}