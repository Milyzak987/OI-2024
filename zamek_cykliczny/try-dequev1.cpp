// deque no long longs, addOne
#include <deque>
#include <iostream>
#include <string>

using namespace std;

deque<int> q;
int res = 0;
int nines = 0;

bool oneZeros() {
    if (q.front() == 1) {
        if (q.size() == 1) {
            return true;
        }
        for (int i = 1; i < q.size(); i++) {
            if (q[i] != 0) {
                return false;
            }
        }
        res++;
        return true;
    }
    return false;
}

void addOne() {
    int i = q.size() - 1;
    while (i >= 0 && q[i] == 9) {
        q[i] = 0;
        i--;
    }
    if (i >= 0) {
        q[i]++;
    } else {
        q.push_front(1);
    }
    res++;
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
    deque<int> numbersAfter;
    int start = (q.size() > 8) ? q.size() - 8 : 0;
    for (int i = q.size() - 1; i >= start; i--) {
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

    int consecutiveNines = 0;
    int i = q.size() - numbersAfter.size() - 1;
    while (i >= 0 && q[i] == 9) {
        consecutiveNines++;
        i--;
    }

    int positionFromEnd = numbersAfter.size();

    int base = 1;
    for (int i = 0; i < positionFromEnd; i++) {
        base *= 10;
    }

    string nums;
    for (auto x : numbersAfter) {
        nums.push_back((x + '0'));
    }
    int moveDif = base - stoi(nums) - 1;

    int addDif = 0;
    for (auto x : numbersAfter) {
        // cout << x;
        if (x != 0) {
            addDif += 9 - x;
        }
    }

    int fullDif = moveDif - addDif;
    // cout << "\n" << fullDif << " " << consecutiveNines << "\n";
    if (fullDif <= consecutiveNines) {
        // cout << "OOOO SPECIAL CASE" << "\n";
        for (int i = 0; i < moveDif; i++) {
            addOne();
        }
    }
}

void endNines() {
    if (q.back() != 0) {
        int i = q.size() - 2;
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

    int i = 0;
    while (nines != q.size()) {
        while (q.back() != 9 && q.back() != 0) {
            addOne();
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