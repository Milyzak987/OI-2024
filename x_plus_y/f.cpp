#include <iostream>
using namespace std;
typedef long long ll;

const int R = 1 << 18;
ll tree[R * 2];

void update(int l, int r, ll x) {
    l += R;
    r += R;
    tree[l] += x;
    if (l != r) {
        tree[r] += x + (r - l); // Dodajemy rosnącą wartość w punkcie r
    }
    while (l / 2 != r / 2) {
        if (l % 2 == 0) { // Prawy sąsiad na lewym poddrzewie
            tree[l + 1] += x;
        }
        if (r % 2 == 1) { // Lewy sąsiad na prawym poddrzewie
            tree[r - 1] += x + (r - l); // Zwiększ o różnicę
        }
        l /= 2;
        r /= 2;
    }
}

ll query(int v) {
    v += R;
    ll res = 0;
    while (v > 0) {
        res += tree[v];
        v /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) { // Dodaj na przedziale
            int l, r;
            ll x;
            cin >> l >> r >> x;
            update(l, r, x);
        } else if (type == 2) { // Odczytaj wartość z punktu
            int v;
            cin >> v;
            cout << query(v) << '\n';
        }
    }

    return 0;
}