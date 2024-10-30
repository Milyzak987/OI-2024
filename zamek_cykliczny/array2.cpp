// array
#include <deque>
#include <iostream>
#include <string>
using namespace std;

const long long MAXN = 1e6 + 7;
long long lock[MAXN];

bool oneZeros(long long n, long long &res) {
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

long long endNines(long long n) {
    long long i = n - 2;
    long long count = 0;
    while (i >= 0 && lock[i] == 9) {
        count++;
        i--;
    }
    return count;
}

void nineCase(long long n, long long &res) {
    deque<long long> suffix;
    long long start = max(n - 8, 0ll);

    for (long long i = n - 1; i >= start; i--) {
        suffix.push_front(lock[i]);
    }
    if (suffix.front() != 9) {  // brak 9 na osmym miejscu od konca
        return;
    }

    while (suffix.front() == 9) {
        suffix.pop_front();
        if (suffix.empty()) {  // same 9 na koncu
            return;
        }
    }
    long long lim = suffix.size();

    long long j = n - lim - 1, nines = 0;
    while (j >= 0 && lock[j] == 9) {
        j--;
        nines++;
    }

    long long moveDif = 0, base = 1, addDif = -1;
    for (long long i = n - 1; i >= n - lim; i--) {
        if (lock[i] != 0) {
            addDif += 10 - lock[i];
        }
        moveDif += (9 - lock[i]) * base;
        base *= 10;
    }
    long long fullDif = moveDif - addDif;
    // cout << nines << " " << moveDif << " " << fullDif << "\n";
    if (fullDif < nines) {
        res += moveDif;
        for (long long i = n - 1; i >= n - lim; i--) {
            lock[i] = 9;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    long long n = s.length();
    for (long long i = 0; i < n; i++) {
        lock[i] = s[i] - '0';
    }

    long long res = 0;
    if (oneZeros(n, res)) {
        cout << res;
        return 0;
    }

    nineCase(n, res);

    long long count = endNines(n);
    // cout << count << " " << res << "\n";
    if (lock[n - 1] == 0) {
        res += count;
    } else {
        res += 9 - lock[n - 1];
    }

    long long r = n - count - 1;
    // cout << lock[n - 1] << "\n";
    for (long long i = 0; i < r; i++) {
        if (lock[i] != 0) {
            res += 10 - lock[i];
        }
    }

    cout << res + 2;

    return 0;
}
