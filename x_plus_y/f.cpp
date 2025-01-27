#include <iostream>
using namespace std;
typedef long long ll;

const int R = 1 << 18;  // Rozmiar drzewa
ll tree[R * 2], lazy[R * 2];  // Tablica drzewa i lazy propagation

// Funkcja propagująca zmiany na dzieci węzła
void push(int node, int l, int r) {
    if (lazy[node] != 0) {
        int mid = (l + r) / 2;
        int left = node * 2, right = node * 2 + 1;
        
        // Propagowanie wartości lazy do dzieci
        tree[left] += lazy[node] * (mid - l + 1);
        tree[right] += lazy[node] * (r - mid);
        
        // Przekazywanie informacji o laziness do dzieci
        lazy[left] += lazy[node];
        lazy[right] += lazy[node];
        
        lazy[node] = 0;
    }
}

// Funkcja do aktualizacji wartości w przedziale [l, r]
void update(int l, int r, ll x) {
    l += R;  // Przechodzimy do odpowiednich węzłów w drzewie
    r += R;
    
    int L = l, R = r;
    while (l <= r) {
        if (l % 2 == 1) {  // Jeżeli l jest nieparzyste, aktualizujemy węzeł
            tree[l] += x;
            lazy[l] += x;
            l++;
        }
        if (r % 2 == 0) {  // Jeżeli r jest parzyste, aktualizujemy węzeł
            tree[r] += x;
            lazy[r] += x;
            r--;
        }
        l /= 2;  // Przechodzimy w górę drzewa
        r /= 2;
    }
}

// Funkcja do odczytu wartości z punktu v
ll query(int v) {
    v += R;  // Przechodzimy do odpowiedniego węzła
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
    cin >> n >> q;  // Liczba punktów i liczba zapytań

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {  // Dodaj na przedziale
            int l, r;
            ll x;
            cin >> l >> r;
            update(l, r, 1);  // Dodajemy 1 na przedziale
        } else if (type == 2) {  // Odczytaj wartość z punktu
            int v;
            cin >> v;
            cout << query(v) << '\n';
        }
    }

    return 0;
}