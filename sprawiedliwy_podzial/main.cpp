// works 100
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct item {
    long long A, B, i;
};

const long long INF = 1e18;
const int MAXN = 5e5 + 7;
vector<item> values(MAXN);
vector<item> in(MAXN);
vector<bool> ans(MAXN);

bool comp(const item &a, const item &b) { return a.A > b.A; }

bool checker(int n) {
    long long Aa = 0, Ba = 0, Ab = 0, Bb = 0, minAb = INF, minBa = INF;
    for (int i = 0; i < n; i++) {
        if (ans[i] == 0) {
            Aa += in[i].A;
            Ab += in[i].B;
            minAb = min(minAb, in[i].B);
        } else {
            Ba += in[i].A;
            Bb += in[i].B;
            minBa = min(minBa, in[i].A);
        }
    }
    if (Aa >= Ba - minBa && Bb >= Ab - minAb) {
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
        item x;
        cin >> x.A;
        x.i = i;
        values[i] = x;
    }
    for (int i = 0; i < n; i++) {
        cin >> values[i].B;
    }

    in = values;

    sort(values.begin(), values.begin() + n, comp);

    long long sumA = 0, sumB = 0;
    for (int i = 0; i < n; i++) {
        item x = values[i];
        if (sumA < sumB) {
            sumA += x.A;
            ans[x.i] = 1;
        } else {
            sumB += x.A;
            ans[x.i] = 0;
        }
    }

    if (!checker(n)) {
        for (int i = 0; i < n; i++) {
            ans[i] = !ans[i];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}