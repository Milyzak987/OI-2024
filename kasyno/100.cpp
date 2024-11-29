//
// Jan Zachar 11/10/2024
// oi32
// Kasyno
//
#include "kaslib.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

#define ERA_SIZE 8000000
// #define ERA_SIZE21000
// #define ERA_SIZE100000
vector<int64_t> prim;
vector<int64_t> maxp;
bool era[ERA_SIZE];
int64_t n = 1;

void init() {
    for (int i = 2; i * i < ERA_SIZE; i++) {
        if (era[i])
            continue;
        for (int j = i * i; j < ERA_SIZE; j += i)
            era[j] = true;
    }

    maxp.reserve(700000);
    for (int i = 2; i < ERA_SIZE; i++) {
        if (era[i])
            continue;
        prim.push_back(i);
    }

    maxp.reserve(700000);
    for (auto &u : prim) {
        int64_t p = u;
        while (p <= n / u)
            p *= u;
        maxp.push_back(p);
    }
}

bool guess(int64_t &p) {
    p = 1;
    for (int i = 0; i < (int)prim.size(); i++) {
        int j = i;
        int64_t x = 1;
        while (j < (int)prim.size() && x < n / prim[j]) {
            x *= prim[j];
            j++;
        }
        j--;

        int64_t q = Pytaj(x);
        while (i <= j) {
            if (q % prim[i] == 0)
                p *= Pytaj(maxp[i]);
            i++;
        }
        i--;

        if (p >= n / prim[i])
            return true;
        if (i > 10 && p < 200ll)
            return false;
        if (i > 30 && p < 16'000ll)
            return false;
        if (i > 100 && p < 900'000ll)
            return false;
        if (i > 250 && p < 600'000'000ll)
            return false;
        if (i > 1200 && p < 3'000'000'000'000ll)
            return false;
        if (i > 70000 && p < 10'000'000'000'000ll)
            return false;
    }

    return false;
}

int main() {
    n = DajN();
    init();
    cout << prim.size();
    while (true) {
        int64_t p;
        if (guess(p))
            Odpowiedz(p);
        else
            Szturchnij();
    }

    return 0;
}