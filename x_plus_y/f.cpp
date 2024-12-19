#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Globalne zmienne
vector<map<int, int>> tree; // Drzewo przedziałowe przechowujące mapy
vector<int> arr;            // Tablica z wartościami run
int n;

// Funkcja do budowy drzewa przedziałowego
void build(int node, int start, int end) {
    if (start == end) {
        tree[node][arr[start]]++;
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        for (const auto& [key, value] : tree[2 * node]) {
            tree[node][key] += value;
        }
        for (const auto& [key, value] : tree[2 * node + 1]) {
            tree[node][key] += value;
        }
    }
}

// Funkcja do aktualizacji wartości w drzewie przedziałowym
void update(int node, int start, int end, int idx, int old_val, int new_val) {
    if (start == end) {
        tree[node][old_val]--;
        if (tree[node][old_val] == 0) tree[node].erase(old_val);
        tree[node][new_val]++;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, old_val, new_val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, old_val, new_val);
        }
        tree[node].clear();
        for (const auto& [key, value] : tree[2 * node]) {
            tree[node][key] += value;
        }
        for (const auto& [key, value] : tree[2 * node + 1]) {
            tree[node][key] += value;
        }
    }
}

// Funkcja do obsługi zapytania o liczność wartości x na przedziale [L, R]
int query(int node, int start, int end, int L, int R, int x) {
    if (R < start || end < L) return 0; // Przedziały się nie nakładają
    if (L <= start && end <= R) {
        return tree[node].count(x) ? tree[node][x] : 0; // Cały przedział zawiera się w zapytaniu
    }
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, L, R, x) +
           query(2 * node + 1, mid + 1, end, L, R, x);
}

// Funkcja główna
int main() {
    int q;
    cin >> n >> q;

    arr.resize(n);
    tree.resize(4 * n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Budowa drzewa
    build(1, 0, n - 1);

    while (q--) {
        char type;
        cin >> type;

        if (type == '?') {
            int l, r, x;
            cin >> l >> r >> x;
            cout << query(1, 0, n - 1, l - 1, r - 1, x) << endl;
        } else if (type == '!') {
            int idx, x;
            cin >> idx >> x;
            idx--; // Przejście na indeksowanie od 0
            update(1, 0, n - 1, idx, arr[idx], x);
            arr[idx] = x;
        }
    }

    return 0;
}