#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5 + 7;
vector<pair<int, int>> worth(MAXN);
vector<bool> whichOne(MAXN);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> worth[i].first;
        worth[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
    }

    sort(worth.begin(), worth.begin() + n, greater<pair<int, int>>());

    long long sumA = 0, sumB = 0;

    for (int i = 0; i < n; i++) {
        pair<int, int> x = worth[i];
        if (sumA < sumB) {
            whichOne[x.second] = true;
            sumA += x.first;
        } else {
            sumB += x.first;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << whichOne[i] << " ";
    }

    return 0;
}