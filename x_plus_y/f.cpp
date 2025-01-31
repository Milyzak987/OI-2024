#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> events;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int day;
            cin >> day;
            events.emplace_back(day, i);
        }
    }

    sort(events.begin(), events.end());

    vector<int> freq(n, 0);
    int count = 0;
    int min_len = INT_MAX;
    int left = 0;

    for (int right = 0; right < events.size(); ++right) {
        int film = events[right].second;
        if (freq[film] == 0) {
            ++count;
        }
        ++freq[film];

        while (count == n) {
            int current_len = events[right].first - events[left].first + 1;
            if (current_len < min_len) {
                min_len = current_len;
            }

            int left_film = events[left].second;
            --freq[left_film];
            if (freq[left_film] == 0) {
                --count;
            }
            ++left;
        }
    }

    cout << min_len << endl;

    return 0;
}