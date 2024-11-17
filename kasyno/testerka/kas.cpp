#include <cmath>
#include <iostream>
#include <vector>

#include "kaslib.h"

using namespace std;

vector<long long> primes;

void gen(long long L) {
    primes.push_back(2);
    long long x = 3;

    while (primes.size() < L) {
        bool isPrime = true;
        long long sqrtX = sqrt(x);

        for (long long prime : primes) {
            if (prime > sqrtX) break;
            if (x % prime == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) {
            primes.push_back(x);
        }
        x += 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n = DajN();
    long long lim = 3000;
    gen(lim);

    while (true) {
        long long il = 1;

        long long combined = 1;
        int i = 0, start = 0;
        for (auto x : primes) {
            if (combined * x <= 0 || combined * x > n/primes.back()) {
                long long gcd = Pytaj(combined);
                for (int p = start; p <= i; p++) {
                    if (gcd % primes[p] == 0) {
                        long long cur = primes[p];
                        while (cur * primes[p] <= n && Pytaj(cur * primes[p]) == cur * primes[p]) {
                            cur *= primes[p];
                        }

                        il *= cur;
                    }
                }
                start = i;
                combined = 1;
            }
            combined *= x;
            i++;
        }
        if (il == 1 || n / il > primes.back()) {
            Szturchnij();
        } else {
            Odpowiedz(il);
        }
    }
}