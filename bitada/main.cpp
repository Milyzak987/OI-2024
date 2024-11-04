#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MOD = 1e9+7;

vector<vector<int>> bitadaTree, bajtogrodTree;
vector<vector<int>> dp;
int n, m, k;

// DFS do obliczania możliwości DP dla mapowania węzłów Bitady na węzły Bajtogrodu
void dfs(int u, int parent, int root) {
    dp[u][root] = 1;
    for (int v : bitadaTree[u]) {
        if (v == parent) continue;
        for (int w : bajtogrodTree[root]) {
            if (w != parent) {
                dfs(v, u, w);
                dp[u][root] = (dp[u][root] * dp[v][w]) % k;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m >> k;
    
    bitadaTree.resize(n+1);
    bajtogrodTree.resize(m+1);
    dp.resize(n+1, vector<int>(m+1, 0));
    
    // Wczytanie krawędzi Bitady
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        bitadaTree[u].push_back(v);
        bitadaTree[v].push_back(u);
    }
    
    // Wczytanie krawędzi Bajtogrodu
    for (int i = 0; i < m - 1; i++) {
        int u, v;
        cin >> u >> v;
        bajtogrodTree[u].push_back(v);
        bajtogrodTree[v].push_back(u);
    }

    // Uruchom DFS dla każdego węzła Bajtogrodu, aby obliczyć wartości DP
    int result = 0;
    for (int root = 1; root <= m; root++) {
        fill(dp.begin(), dp.end(), vector<int>(m + 1, 0));
        dfs(1, -1, root);
        result = (result + dp[1][root]) % k;
    }

    cout << result << endl;
    return 0;
}
