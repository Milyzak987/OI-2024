#include <deque>
#include <iostream>
#include <string>

using namespace std;

deque<long long> q;
long long res = 0;
long long nines = 0;

bool oneZeros() {
    if (q.front() == 1) {
        if (q.size() == 1) {
            return true;
        }
        for (long long i = 1; i < q.size(); i++) {
            if (q[i] != 0) {
                return false;
            }
        }
        res++;
        return true;
    }
    return false;
}

void addToNine() {
    res += 9 - q.back();
    q.pop_back();
    q.push_back(9);
}

void move() {
    q.push_back(q.front());
    q.pop_front();
    while (q.front() == 0) {
        q.pop_front();
    }
    res++;
}

void nineCase() {
    deque<long long> numbersAfter;
    long long start = (q.size() > 9) ? q.size() - 9 : 0;
    for (long long i = q.size() - 1; i >= start; i--) {
        numbersAfter.push_front(q[i]);
    }
    if (numbersAfter.front() != 9) {
        return;
    }

    while (numbersAfter.front() == 9) {
        numbersAfter.pop_front();
        if (numbersAfter.empty()) {
            return;
        }
    }

    long long consecutiveNines = 0;
    long long i = q.size() - numbersAfter.size() - 1;
    while (i >= 0 && q[i] == 9) {
        consecutiveNines++;
        i--;
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

void endNines() {
    if (q.back() != 0) {
        long long i = q.size() - 2;
        while (i >= 0 && q[i] == 9) {
            nines++;
            i--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string str;
    cin >> str;

    for (auto x : str) {
        q.push_back(x - '0');
    }

    if (oneZeros()) {
        cout << res;
        return 0;
    }

    nineCase();
    endNines();

    long long i = 0;
    while (nines != q.size()) {
        if (q.back() != 9 && q.back() != 0) {
            addToNine();
        }
        if (q.back() == 9) {
            nines++;
        }
        if (nines != q.size()) {
            move();
        }
    }

    cout << res + 2;

    return 0;
}