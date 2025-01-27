#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;
long long tree[4 * MAXN], lazy_add[4 * MAXN], lazy_inc[4 * MAXN];

void propagate(int node, int l, int r) {
    int mid = (l + r) / 2;
    int left = node * 2, right = node * 2 + 1;

    // Apply lazy_add and lazy_inc to current node
    tree[node] += lazy_add[node] * (r - l + 1) + lazy_inc[node] * (r - l) * (r - l + 1) / 2;

    // Pass lazy updates to children
    if (l != r) {
        lazy_add[left] += lazy_add[node];
        lazy_add[right] += lazy_add[node] + lazy_inc[node] * (mid - l + 1);
        lazy_inc[left] += lazy_inc[node];
        lazy_inc[right] += lazy_inc[node];
    }

    lazy_add[node] = 0;
    lazy_inc[node] = 0;
}

void update(int node, int l, int r, int ql, int qr, long long add, long long inc) {
    propagate(node, l, r);

    if (qr < l || ql > r) return; // Out of range
    if (ql <= l && r <= qr) { // Fully in range
        lazy_add[node] += add;
        lazy_inc[node] += inc;
        propagate(node, l, r);
        return;
    }

    // Partially in range
    int mid = (l + r) / 2;
    update(node * 2, l, mid, ql, qr, add, inc);
    update(node * 2 + 1, mid + 1, r, ql, qr, add + inc * max(0, mid - max(ql, l) + 1), inc);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(int node, int l, int r, int idx) {
    propagate(node, l, r);

    if (l == r) return tree[node];
    int mid = (l + r) / 2;

    if (idx <= mid)
        return query(node * 2, l, mid, idx);
    else
        return query(node * 2 + 1, mid + 1, r, idx);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q; // liczba punktów i liczba zapytań

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) { // Dodaj na przedziale
            int l, r;
            cin >> l >> r;
            update(1, 1, n, l, r, 1, 1);
        } else if (type == 2) { // Odczytaj wartość z punktu
            int idx;
            cin >> idx;
            cout << query(1, 1, n, idx) << '\n';
        }
    }

    return 0;
}