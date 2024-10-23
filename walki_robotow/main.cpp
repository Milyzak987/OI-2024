#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;
const int MAXN = 2e5 + 7;
vector<pair<int, int>> bots(MAXN);
bool isHigher[MAXN];
int lowest[MAXN];
int highest[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> bots[i].first >> bots[i].second;
    }

    sort(bots.begin(), bots.begin() + n, greater<pair<int, int>>());

    int maxx = 0, higherCount = 0;
    for (int i = 0; i < n; i++) {
        if (bots[i].second > maxx) {
            maxx = bots[i].second;
            isHigher[i] = true;
            higherCount++;
        } else {
            isHigher[i] = false;
        }
    }

    if (higherCount % 2 == 0) {
        cout << "TAK";
        return 0;
    }

    // lowest
    lowest[0] = INF;
    for (int i = 1; i < n; i++) {
        if (isHigher[i]) {
            lowest[i] = lowest[i - 1];
        } else {
            lowest[i] = min(lowest[i - 1], bots[i].second);
        }
    }

    // highest
    if (isHigher[n - 1]) {
        highest[n - 1] = 0;
    } else {
        highest[n - 1] = bots[n - 1].second;
    }
    for (int i = n - 2; i >= 0; i--) {
        if (isHigher[i]) {
            highest[i] = highest[i + 1];
        } else {
            highest[i] = max(highest[i + 1], bots[i].second);
        }
    }

    // check
    for (int i = 0; i < n; i++) {
        if (isHigher[i]) {
            if (lowest[i] < bots[i].second || highest[i] > bots[i].second) {
                cout << "TAK";
                return 0;
            }
        }
    }
    cout << "NIE";
    return 0;
}