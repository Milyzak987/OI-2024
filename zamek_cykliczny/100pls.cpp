#include <deque>
#include <iostream>
#include <string>

using namespace std;

const long long INF = 1e18;
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
    long long minMoveDif = INF;
    long long bestPositionFromEnd = 0;
    deque<long long> bestNumbersAfter;
    
    // Sprawdzamy końcówki o długości od 1 do 7
    for (long long length = 1; length <= 7 && length <= q.size(); length++) {
        deque<long long> numbersAfter;
        
        // Tworzymy końcówkę o danej długości
        for (long long i = q.size() - length; i < q.size(); i++) {
            numbersAfter.push_back(q[i]);
        }
        
        // Sprawdzamy, czy końcówka zaczyna się od 9
        if (numbersAfter.front() != 9) {
            continue;
        }

        // Usuwamy początkowe dziewiątki
        while (!numbersAfter.empty() && numbersAfter.front() == 9) {
            numbersAfter.pop_front();
        }

        // Jeśli cała końcówka to same dziewiątki, to pomijamy
        if (numbersAfter.empty()) {
            continue;
        }

        long long consecutiveNines = 0;
        long long i = q.size() - numbersAfter.size() - 1;
        while (i >= 0 && q[i] == 9) {
            consecutiveNines++;
            i--;
        }

        long long positionFromEnd = numbersAfter.size();

        // Obliczamy liczbę reprezentowaną przez końcówkę bez użycia stoll()
        long long numValue = 0;
        long long base = 1;
        for (long long j = numbersAfter.size() - 1; j >= 0; j--) {
            numValue += numbersAfter[j] * base;
            base *= 10;
        }

        // Obliczamy różnicę potrzebną do zamiany liczby na pełne 9's
        long long moveDif = base - numValue - 1;

        long long addDif = 0;
        for (auto x : numbersAfter) {
            if (x != 0) {
                addDif += 9 - x;
            }
        }

        long long fullDif = moveDif - addDif;
        if (fullDif <= consecutiveNines) {
            // Zapisujemy minimalny moveDif i najlepszą końcówkę
            if (moveDif < minMoveDif) {
                minMoveDif = moveDif;
                bestPositionFromEnd = positionFromEnd;
                bestNumbersAfter = numbersAfter;
            }
        }
    }

    // Jeśli znaleziono najlepszą końcówkę
    if (minMoveDif != INF) {
        res += minMoveDif;
        for (long long i = 0; i < bestPositionFromEnd; i++) {
            q.pop_back();
        }
        for (long long i = 0; i < bestPositionFromEnd; i++) {
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