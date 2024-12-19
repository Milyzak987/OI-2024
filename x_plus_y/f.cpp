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
                    long long di = 4 * abs(i - a); // odległość pozioma
                    long long dj = 4 * abs(j - b); // odległość pionowa
                    long long d2 = di * di + dj * dj; // kwadrat odległości
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