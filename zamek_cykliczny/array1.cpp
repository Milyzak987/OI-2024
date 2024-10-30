// array
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 1e6 + 7;
const int INF = 1e9;
int lock[MAXN];

bool oneZeros(int n, int &res) {
    if (lock[0] == 1) {
        if (n == 1) {
            return true;
        }
        for (long long i = 1; i < n; i++) {
            if (lock[i] != 0) {
                return false;
            }
        }
        res++;
        return true;
    }
    return false;
}

int endNines(int n, int lim) {
    int i = n - lim;
    int count = 0;
    while (i >= 0 && lock[i] == 9) {
        count++;
        i--;
    }
    return count;
}

void nineCase(int n, int &res, int &minLim) {
    int minDif = INF;
    for (int t = 2; t <= 8; t++) {
        long long start = max(n - 8, 0);

        int j = start - 1, nines = 0;
        while (j >= 0 && lock[j] == 9) {
            j--;
            nines++;
        }

        int moveDif = 0, base = 1, addDif = 0;
        for (long long i = n - 1; i >= start; i--) {
            if (lock[i] != 0) {
                addDif += 9 - lock[i];
            }
            moveDif += (9 - lock[i]) * base;
            base *= 10;
        }
        int fullDif = moveDif - addDif;
        // cout << nines << " " << moveDif << "\n";
        if (fullDif <= nines && moveDif < minDif) {
            minDif = moveDif;
            minLim = t + 1;
        }
    }
    if (minDif != INF) {
        res += minDif;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    int n = s.length();
    for (int i = 0; i < n; i++) {
        lock[i] = s[i] - '0';
    }

    int res = 0, minLim = 2;
    if (oneZeros(n, res)) {
        cout << res;
        return 0;
    }

    nineCase(n, res, minLim);

    int count = endNines(n, minLim);
    // cout << count << " " << res << "\n";
    if (lock[n - 1] == 0 && res == 0) {
        res += count;
    }

    if (lock[n - 1] != 0 && res == 0) {
        res += 9 - lock[n - 1];
    }

    count += minLim - 1;
    int r = n - count;
    for (int i = 0; i < r; i++) {
        if (lock[i] != 0) {
            res += 10 - lock[i];
        }
    }

    cout << res + 2;

    return 0;
}