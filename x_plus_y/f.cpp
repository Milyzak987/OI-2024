#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        ll l, r;
        cin >> l >> r;

        // Sprawdzenie nieskończoności
        if (l <= 0 && r >= 0) {
            cout << -1 << '\n';
            continue;
        }

        ll count = 0;

        // Iteracja po x1 i x2
        for (ll x1 = 1; x1 * x1 <= r; ++x1) {
            for (ll x2 = x1; x2 <= r; ++x2) {
                ll b = -(x1 + x2);
                ll c = x1 * x2;
                ll sum = b + c;

                if (sum < l) break; // Jeśli sum < l, dalsze x2 nie będą poprawne
                if (sum <= r) count++;
            }
        }

        cout << count << '\n';
    }
}

int main() {
    solve();
    return 0;
}