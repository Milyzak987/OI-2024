#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Funkcja obliczająca minimalny koszt dla jednego wymiaru
pair<long long, int> minimalCostForDimension(const vector<int>& weights, int length) {
    vector<long long> prefixSum(length + 1, 0), weightedSum(length + 1, 0);

    // Oblicz prefix sumy
    for (int i = 1; i <= length; ++i) {
        prefixSum[i] = prefixSum[i - 1] + weights[i - 1];
        weightedSum[i] = weightedSum[i - 1] + weights[i - 1] * i;
    }

    long long minCost = LLONG_MAX;
    int bestPosition = 0;

    // Oblicz koszt dla każdej pozycji
    for (int pos = 0; pos <= length; ++pos) {
        long long leftSum = prefixSum[pos] * pos - weightedSum[pos];
        long long rightSum = (weightedSum[length] - weightedSum[pos]) - (prefixSum[length] - prefixSum[pos]) * pos;
        long long cost = leftSum + rightSum;

        if (cost < minCost) {
            minCost = cost;
            bestPosition = pos;
        }
    }

    return {minCost, bestPosition};
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> c(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> c[i][j];

    // Obliczenie wag dla wierszy (poziomy wymiar)
    vector<int> rowWeights(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            rowWeights[i] += c[i][j];
        }
    }

    // Obliczenie wag dla kolumn (pionowy wymiar)
    vector<int> colWeights(m, 0);
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            colWeights[j] += c[i][j];
        }
    }

    // Minimalny koszt i najlepsza pozycja dla wierszy
    auto [rowCost, bestRow] = minimalCostForDimension(rowWeights, n);

    // Minimalny koszt i najlepsza pozycja dla kolumn
    auto [colCost, bestCol] = minimalCostForDimension(colWeights, m);

    // Wynik
    cout << rowCost + colCost << endl;
    cout << bestRow << " " << bestCol << endl;

    return 0;
}