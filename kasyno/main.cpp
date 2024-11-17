#include "kaslib.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

vector<long long> primes;

void gen(long long N) {
    primes.push_back(2);
    long long x = 3;
    while (primes.size() < N) {
        bool p = true;
        for (long long i = 0; i < primes.size(); i++) {
            if (x % primes[i] == 0) {
                p = false;
                break;
            }
        }
        if (p) {
            primes.push_back(x);
        }
        x += 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n = DajN();
    long long lim = 1000;
    gen(lim);

    long long bajtalary = 1e7;

    while (bajtalary > 0) {
        long long il = 1;
        long long p = -1, q = -1;
        for (long long i = 0; i < primes.size() - 1; i++) {
            if (Pytaj(primes[i]) != 1) {
                long long j = 2;
                long long cur = primes[i];
                long long pot = pow(primes[i], 2);
                while (Pytaj(pot) == pot) {
                    j++;
                    cur = pot;
                    pot = pow(primes[i], j);
                }
                il *= cur;
            }
        }
        if (il == 1) {
            Szturchnij();
            bajtalary--;
        } else if (Pytaj(il * primes.back()) == il) {
            Odpowiedz(il);
            bajtalary--;
        } else {
            Szturchnij();
            bajtalary--;
        }
    }
}