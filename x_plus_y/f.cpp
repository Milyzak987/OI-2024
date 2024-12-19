#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> c(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> c[i][j];

    long long minCost = LLONG_MAX;
    int bestA = 0, bestB = 0;

    for (int a = 0; a <= n; ++a) { // poziome linie
        for (int b = 0; b <= m; ++b) { // pionowe linie
            long long cost = 0;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    // Skalowanie współrzędnych
                    int wiatrakX = 2 * i + 1; // pozycja wiatraka w skali całkowitej
                    int wiatrakY = 2 * j + 1; // pozycja wiatraka w skali całkowitej
                    int obozX = 2 * a;       // pozycja obozu w skali całkowitej
                    int obozY = 2 * b;       // pozycja obozu w skali całkowitej

                    // Obliczanie odległości w skali całkowitej
                    long long dx = 4 * (wiatrakX - obozX); // odległość pozioma
                    long long dy = 4 * (wiatrakY - obozY); // odległość pionowa
                    long long d2 = dx * dx + dy * dy;      // kwadrat odległości

                    cost += c[i][j] * d2;
                }
            }

            if (cost < minCost) {
                minCost = cost;
                bestA = a;
                bestB = b;
            }
        }
    }

    cout << minCost << endl;
    cout << bestA << " " << bestB << endl;

    return 0;
}