#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

vector<int> graph[MAXN];
int depth[MAXN];
bool visited[MAXN];

// BFS do obliczenia odległości od pokoju 1
void bfs(int start, int n) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    depth[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                depth[neighbor] = depth[current] + 1;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Obliczanie odległości od pokoju 1
    bfs(1, n);

    // Znajdź liście (pokoje najdalsze od 1)
    vector<int> leaves;
    for (int i = 1; i <= n; ++i) {
        if (graph[i].size() == 1) { // Liść ma tylko jednego sąsiada
            leaves.push_back(depth[i]);
        }
    }

    // Posortuj odległości liści od największej do najmniejszej
    sort(leaves.rbegin(), leaves.rend());

    // Oblicz minimalną maksymalną odległość po wykorzystaniu k miauknięć
    int result = leaves[k]; // Po usunięciu k najdalszych połączeń

    cout << result << "\n";

    return 0;
}