// string
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
    long long start = (n > 7) ? n - 7 : 0;
    for (long long i = n - 1; i >= start; i--) {
        numbersAfter.push_front(q[i]);
    }

    long long consecutiveNines = 0;
    long long j = q.size() - numbersAfter.size() - 1;
    while (j >= 0 && q[j] == 9) {
        consecutiveNines++;
        j--;
    }

    long long positionFromEnd = numbersAfter.size();

    long long base = 1;
    for (long long i = 0; i < positionFromEnd; i++) {
        base *= 10;
    }

    string nums;
    for (auto x : numbersAfter) {
        nums.push_back((x + '0'));
    }
    long long moveDif = base - stoll(nums) - 1;

    long long addDif = 0;
    for (auto x : numbersAfter) {
        if (x != 0) {
            addDif += 9 - x;
        }
    }

    long long fullDif = moveDif - addDif;
    if (fullDif <= consecutiveNines) {
        res += moveDif;
        for (long long i = 0; i < positionFromEnd; i++) {
            q.pop_back();
        }
        for (long long i = 0; i < positionFromEnd; i++) {
            q.push_back(9);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    int n = s.length();
    for(int i = 0; i < n; i++){
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