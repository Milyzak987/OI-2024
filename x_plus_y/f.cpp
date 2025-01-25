#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5 + 7;

void solve() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    while (q--) {
        ll l, r;
        cin >> l >> r;

        if (l <= 0 && r >= 0) {
            cout << -1 << '\n'; // Infinite solutions
            continue;
        }

        ll result = 0;
        for (ll s = l; s <= r; ++s) {
            // Count pairs (x1, x2) such that x1 + x2 = -b and x1 * x2 = c
            // and b + c = s
            // Rearrange: b = s - c
            for (ll x1 = 1; x1 * x1 <= abs(s); ++x1) {
                if (s % x1 == 0) {
                    ll x2 = s / x1;
                    if (x1 <= x2) result++;
                }
            }
        }

        cout << result << '\n';
    }
}

int main() {
    solve();
    return 0;
}