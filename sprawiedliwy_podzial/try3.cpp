// doesn't work
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

struct items {
    int A, B, i;
};

bool compA(const items &a, const items &b) { return a.A > b.A || (a.A == b.A && a.B < b.B); }
bool compB(const items &a, const items &b) { return a.B > b.B || (a.B == b.B && a.A < b.A); }

const long long INF = 1e18;
const int MAXN = 5e5 + 7;
vector<bool> ans(MAXN);
deque<items> worthA, worthB;
bool visited[MAXN];
vector<pair<long long, long long>> in(MAXN);

bool checker(int n) {
    long long sumAgrA = 0, sumAgrB = 0, sumBgrA = 0, sumBgrB = 0;
    long long minA = INF, minB = INF;
    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            sumAgrA += in[i].first;
            sumBgrA += in[i].second;
            minB = min(minB, in[i].second);
        } else {
            sumAgrB += in[i].first;
            sumBgrB += in[i].second;
            minA = min(minA, in[i].first);
        }
    }
    if (sumAgrA >= sumAgrB - minA && sumBgrB >= sumBgrA - minB) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        items x;
        cin >> x.A;
        x.i = i;
        worthA.push_back(x);
        worthB.push_back(x);
        in[i].first = x.A;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        worthA[i].B = x;
        worthB[i].B = x;
        in[i].second = x;
    }

    sort(worthA.begin(), worthA.end(), compA);
    sort(worthB.begin(), worthB.end(), compB);

    // for (auto x : worthB) {
    //     cout << x.A << " ";
    // }
    // cout << "\n";
    // for (auto x : worthB) {
    //     cout << x.B << " ";
    // }
    // cout << "\n";

    long long Aa = 0, Ab = 0, Ba = 0, Bb = 0, lasti;

    while (!worthB.empty() || !worthA.empty()) {
        if (Aa - Ba == Bb - Ab) {
            if ((worthB.front().B - worthB.front().A) > (worthA.front().A - worthA.front().B)) {
                visited[worthB.front().i] = true;
                Ba += worthB.front().A;
                Bb += worthB.front().B;
                ans[worthB.front().i] = 1;
                lasti = worthB.front().i;
                worthB.pop_front();
            } else {
                visited[worthA.front().i] = true;
                Aa += worthA.front().A;
                Ab += worthA.front().B;
                ans[worthA.front().i] = 0;
                lasti = worthA.front().i;
                worthA.pop_front();
            }
        } else if (Aa - Ba < Bb - Ab) {
            Aa += worthA.front().A;
            Ab += worthA.front().B;
            ans[worthA.front().i] = 0;
            visited[worthA.front().i] = true;
            lasti = worthA.front().i;
            worthA.pop_front();
        } else {
            Ba += worthB.front().A;
            Bb += worthB.front().B;
            ans[worthB.front().i] = 1;
            visited[worthB.front().i] = true;
            lasti = worthB.front().i;
            worthB.pop_front();
        }
        while (!worthA.empty() && visited[worthA.front().i]) {
            worthA.pop_front();
        }
        while (!worthB.empty() && visited[worthB.front().i]) {
            worthB.pop_front();
        }
    }

    // if (!checker(n)) {
    //     ans[lasti] = !ans[lasti];
    // }

    if (!checker(n)) {
        cout << "nie dziala\n";
        cout << Aa - Ba << " " << Bb - Ab << "\n";
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}