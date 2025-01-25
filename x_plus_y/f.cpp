#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Funkcja obliczająca liczbę par dla danego przedziału l, r
int countPairs(int l, int r) {
    set<pair<int, int>> uniquePairs;

    for (int x1 = -1000; x1 <= 1000; x1++) {
        for (int x2 = x1; x2 <= 1000; x2++) {
            int b = -(x1 + x2);
            int c = x1 * x2;
            int sum = b + c;
            if (l <= sum && sum <= r) {
                uniquePairs.insert({x1, x2});
            }
        }
    }

    return uniquePairs.size();
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int result = countPairs(l, r);
        cout << result << endl;
    }
    return 0;
}




#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

// Funkcja obliczająca liczbę par
long long countPairsOptimized(int l, int r) {
    if (r - l >= 1000) {
        return -1; // Nieskończoność, gdy zakres pozwala na dowolne pary
    }

    long long count = 0;

    for (int x1 = -1000000; x1 <= 1000000; x1++) {
        for (int x2 = x1; x2 <= 1000000; x2++) {
            int b = -(x1 + x2);
            int c = x1 * x2;
            int sum = b + c;
            if (l <= sum && sum <= r) {
                count++;
            }
            if (sum > r) break; // Optymalizacja - nie sprawdzaj, jeśli suma już wykracza poza zakres
        }
    }

    return count;
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        long long result = countPairsOptimized(l, r);
        cout << result << endl;
    }
    return 0;
}