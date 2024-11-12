// works for n <= 20 (n*2^n), can improve by integrating generator into checker
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5 + 7;
const long long INF = 1e18;
bool b = false;
vector<pair<long long, long long>> valueA(MAXN);
vector<pair<long long, long long>> valueB(MAXN);
vector<bool> ans(MAXN);

bool checker(int n) {
    long long sumAgrA = 0, sumAgrB = 0, sumBgrA = 0, sumBgrB = 0;
    long long minA = INF, minB = INF;
    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            sumAgrA += valueA[i].first;
            sumBgrA += valueB[i].first;
            minB = min(minB, valueB[i].first);
        } else {
            sumAgrB += valueA[i].first;
            sumBgrB += valueB[i].first;
            minA = min(minA, valueA[i].first);
        }
    }
    if (sumAgrA >= sumAgrB - minA && sumBgrB >= sumBgrA - minB) {
        return true;
    }
    return false;
}

void generateBinary(int n, int i) {
    if (i == n) {
        if (checker(n)) {
            b = true;
            for (int j = 0; j < n; j++) {
                cout << ans[j] << " ";
            }
        }
        return;
    }
    if (b)
        return;

    ans[i] = 0;
    generateBinary(n, i + 1);

    ans[i] = 1;
    generateBinary(n, i + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> valueA[i].first;
        valueA[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> valueB[i].first;
        valueA[i].second = i;
    }

    if (n <= 10) {
        generateBinary(n, 0);
    } else {
        sort(valueA.begin(), valueA.begin() + n, greater<pair<long long, long long>>());

        long long sumA = 0, sumB = 0;

        for (int i = 0; i < n; i++) {
            pair<long long, long long> x = valueA[i];
            if (sumA < sumB) {
                ans[x.second] = true;
                sumA += x.first;
            } else {
                sumB += x.first;
            }
        }

        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
    }
    return 0;
}