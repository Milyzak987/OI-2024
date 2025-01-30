#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;
vector<int> graph[MAXN], rev_graph[MAXN];
int in_degree[MAXN], out_degree[MAXN];
int result[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> match_order(n + 1, -1);
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[y].push_back(x);
        rev_graph[x].push_back(y);
        in_degree[x]++;
        out_degree[y]++;
    }

    queue<int> q;
    vector<int> topo;
    
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
            match_order[i] = 0;
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);
        
        for (int v : graph[node]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
                match_order[v] = match_order[node] + 1;
            }
        }
    }

    if ((int)topo.size() < n) {
        fill(result, result + n + 1, -1);
    } else {
        for (int i = 1; i <= n; i++) {
            result[i] = match_order[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}