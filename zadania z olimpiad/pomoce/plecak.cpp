#include <iostream>
using namespace std;

const int MAXN = 1e5 + 7;

long long dp[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, W;
    cin >> n >> W;
    for (int i = 1; i <= n; i++) {
        int w, v;
        cin >> w >> v;
        for (int j = W; j >= w; j--) {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }
    cout << dp[W] << "\n";
}