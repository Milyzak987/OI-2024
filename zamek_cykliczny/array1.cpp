// array
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 1e6 + 7;
int lock[MAXN];

bool oneZeros(int n, int res) {
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

int endNines(int n) {
    int i = n - 2;
    int count = 0;
    while (i >= 0 && lock[i] == 9) {
        count++;
        i--;
    }
    return count;
}

void nineCase(int n) {
    for (int t = 1; t <= 8; t++) {
        long long start = max(n - t, 0);

        int j = start - 1, nines = 0;
        while (j >= 0 && lock[j] == 9){
            j--;
            nines++;
        }

        int dif = 0, base = 1;
        for (long long i = n - 1; i >= start; i--) {
            base *= 10;
            dif += ((9 - lock[i]) * base) - (9 - lock[i]);
        }

        if (dif <= nines) {
            res += moveDif;
            for (long long i = 0; i < positionFromEnd; i++) {
                q.pop_back();
            }
            for (long long i = 0; i < positionFromEnd; i++) {
                q.push_back(9);
            }
        }
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

    int res = 0;
    if (oneZeros(n, res)) {
        cout << res;
        return 0;
    }

    int count = endNines(n);
    if (lock[n - 1] == '0') {
        res += count;
    }

    if (lock[n - 1] != '0') {
        res += 9 - lock[n - 1];
    }

    int r = s.length() - count - 1;
    for (int i = 0; i < r; i++) {
        if (lock[i] != 0) {
            res += 10 - lock[i];
        }
    }

    cout << res + 2;

    return 0;
}