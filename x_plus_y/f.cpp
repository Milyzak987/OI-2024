#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> days(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> days[i][j];
        }
        sort(days[i].begin(), days[i].end());
    }

    int min_days = INT_MAX;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int start = days[i][j];
            int end = start;
            bool valid = true;

            for (int k = 0; k < n; ++k) {
                auto it = lower_bound(days[k].begin(), days[k].end(), start);
                if (it == days[k].end() || *it > end) {
                    valid = false;
                    break;
                }
                end = max(end, *it);
            }

            if (valid) {
                min_days = min(min_days, end - start + 1);
            }
        }
    }

    cout << min_days << endl;

    return 0;
}