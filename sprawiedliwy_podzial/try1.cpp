// doesn't work
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

struct items {
    int A, B, i;
};

bool comp(const items &a, const items &b) { return (a.A - a.B) > (b.A - b.B); }

const int MAXN = 5e5 + 7;
vector<bool> ans(MAXN);
deque<items> worth;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        items x;
        cin >> x.A;
        x.i = i;
        worth.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        cin >> worth[i].B;
    }

    sort(worth.begin(), worth.end(), comp);

    // for (auto x : worth) {
    //     cout << x.A;
    // }
    // cout << "\n";
    // for (auto x : worth) {
    //     cout << x.B;
    // }
    // cout << "\n";

    long long Aa = 0, Ab = 0, Ba = 0, Bb = 0;

    while (!worth.empty()) {
        if (Aa - Ba < Bb - Ab) {
            Aa += worth.front().A;
            Ab += worth.front().B;
            ans[worth.front().i] = 0;
            worth.pop_front();
        } else {
            Ba += worth.back().A;
            Bb += worth.back().B;
            ans[worth.back().i] = 1;
            worth.pop_back();
        }
        // cout << Aa - Ba << " " << Bb - Ab << "\n";
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}