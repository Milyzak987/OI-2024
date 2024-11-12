// Kompatybilne z Tosterem - https://github.com/MikolajKolek/toster
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define ll long long
#define V vector
const ll inf = 1e15;

int n;
V<ll> A, B, odp;
ll sum_a_gr_a, sum_a_gr_b, sum_b_gr_a, sum_b_gr_b;
ll min_a_gr_b = inf, min_b_gr_a = inf;

void ERR(string err) {
    cout << "I " << err;
    exit(0);
}

int main() {
    cin.tie(0)->ios_base::sync_with_stdio(0);
    cin >> n;

    // Odkomentuj poniższą linię, by testować jedynie na testach z małym n.
    // if(n>10) cout << "C", exit(0);

    A.resize(n + 1);
    B.resize(n + 1);
    odp.resize(n + 1);
    FOR(i, 1, n) cin >> A[i];
    FOR(i, 1, n) cin >> B[i];
    // Odkomentuj dla ai = bi
    // B.clear();
    // B = A;
    FOR(i, 1, n) {
        cin >> odp[i];
        if (odp[i] != 0 && odp[i] != 1)
            ERR("Odpowiedź niezgodna z formatem wyjścia.");
    }

    FOR(i, 1, n) {
        if (odp[i] == 0) {
            sum_a_gr_a += A[i];
            sum_b_gr_a += B[i];
            min_b_gr_a = min(min_b_gr_a, B[i]);
        } else {
            sum_a_gr_b += A[i];
            sum_b_gr_b += B[i];
            min_a_gr_b = min(min_a_gr_b, A[i]);
        }
    }

    if (sum_a_gr_a < sum_a_gr_b - min_a_gr_b)
        ERR("Bitek zazdrości Bajtynie.");
    if (sum_b_gr_b < sum_b_gr_a - min_b_gr_a)
        ERR("Bajtyna zazdrości Bitkowi.");

    cout << "C";
    return 0;
}