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

const int MAXN = 5e5 + 7;
vector<bool> ans(MAXN);
deque<items> worthA, worthB;
bool visited[MAXN];

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
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        worthA[i].B = x;
        worthB[i].B = x;
    }

    sort(worthA.begin(), worthA.end(), compA);
    sort(worthB.begin(), worthB.end(), compB);

    for (auto x : worthB) {
        cout << x.A << " ";
    }
    cout << "\n";
    for (auto x : worthB) {
        cout << x.B << " ";
    }
    cout << "\n";

    long long Aa = 0, Ab = 0, Ba = 0, Bb = 0;

    while (!worthB.empty() || !worthA.empty()) {
        if (Aa - Ba == Bb - Ab) {
            if ((worthB.front().B - worthB.front().A) > (worthA.front().A - worthA.front().B)) {
                visited[worthB.front().i] = true;
                Ba += worthB.front().A;
                Bb += worthB.front().B;
                ans[worthB.front().i] = 1;
                worthB.pop_front();
            } else {
                visited[worthA.front().i] = true;
                Aa += worthA.front().A;
                Ab += worthA.front().B;
                ans[worthA.front().i] = 0;
                worthA.pop_front();
            }
        } else if (Aa - Ba < Bb - Ab) {
            Aa += worthA.front().A;
            Ab += worthA.front().B;
            ans[worthA.front().i] = 0;
            visited[worthA.front().i] = true;
            worthA.pop_front();
        } else {
            Ba += worthB.front().A;
            Bb += worthB.front().B;
            ans[worthB.front().i] = 1;
            visited[worthB.front().i] = true;
            worthB.pop_front();
        }
        while (!worthA.empty() && visited[worthA.front().i]) {
            worthA.pop_front();
        }
        while (!worthB.empty() && visited[worthB.front().i]) {
            worthB.pop_front();
        }
    }

    // cout << Aa - Ba << " " << Bb - Ab << "\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}