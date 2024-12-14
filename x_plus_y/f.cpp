#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Wczytanie danych wejściowych
    int n, m;
    cin >> n >> m;

    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) cin >> A[i];
    for (int i = 0; i < n; ++i) cin >> B[i];

    vector<long long> C(m);
    for (int i = 0; i < m; ++i) cin >> C[i];

    long long total_points = 0;

    // Przetwarzamy każdy rodzaj klocków osobno
    for (int j = 0; j < m; ++j) {
        long long available_blocks = C[j];

        // Tworzymy tablicę DP dla aktualnego rodzaju klocków
        vector<long long> dp(available_blocks + 1, 0);

        // Przetwarzanie każdego schematu wieży
        for (int i = 0; i < n; ++i) {
            if (A[i] > B[i]) { // Tylko jeśli budowa wieży ma sens
                for (long long x = available_blocks; x >= A[i]; --x) {
                    dp[x] = max(dp[x], dp[x - A[i]] + 2);
                }
            }
        }

        // Maksymalna liczba punktów dla tego rodzaju klocków
        total_points += dp[available_blocks];
    }

    // Wypisanie wyniku
    cout << total_points << endl;

    return 0;
}