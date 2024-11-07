#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

vector<vector<int>> bitadaTree, bajtogrodTree;
vector<vector<int>> dp;
int n, m, k;

// Funkcja do liczenia wszystkich przypisań przy użyciu DFS
int dfs(int bitadaNode, int bajtogrodNode, vector<bool>& visited) {
    if (dp[bitadaNode][bajtogrodNode] != -1) 
        return dp[bitadaNode][bajtogrodNode];
    
    visited[bajtogrodNode] = true;
    vector<int> bitadaChildren, bajtogrodChildren;
    
    // Zbieramy dzieci obu węzłów
    for (int v : bitadaTree[bitadaNode]) 
        bitadaChildren.push_back(v);
    
    for (int v : bajtogrodTree[bajtogrodNode]) {
        if (!visited[v]) 
            bajtogrodChildren.push_back(v);
    }
    
    int result = 0;

    // Jeżeli liczba dzieci Bitady jest większa niż Bajtogrodu, nie można przypisać
    if (bitadaChildren.size() > bajtogrodChildren.size()) {
        visited[bajtogrodNode] = false;
        return dp[bitadaNode][bajtogrodNode] = 0;
    }
    
    // Przechodzimy przez wszystkie permutacje dzieci z Bajtogrodu
    sort(bajtogrodChildren.begin(), bajtogrodChildren.end());
    do {
        int possibleMappings = 1;
        for (int i = 0; i < bitadaChildren.size(); i++) {
            possibleMappings = (possibleMappings * dfs(bitadaChildren[i], bajtogrodChildren[i], visited)) % k;
            if (possibleMappings == 0) break; // Przerwij, jeśli mapping jest niemożliwy
        }
        result = (result + possibleMappings) % k;
    } while (next_permutation(bajtogrodChildren.begin(), bajtogrodChildren.end()));
    
    visited[bajtogrodNode] = false;
    return dp[bitadaNode][bajtogrodNode] = result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m >> k;
    bitadaTree.resize(n + 1);
    bajtogrodTree.resize(m + 1);
    dp.assign(n + 1, vector<int>(m + 1, -1));
    
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

    int result = 0;
    vector<bool> visited(m + 1, false);
    
    // Próbujemy dopasować korzeń Bitady do każdego wierzchołka Bajtogrodu
    for (int root = 1; root <= m; root++) {
        result = (result + dfs(1, root, visited)) % k;
    }

    cout << result << endl;
    return 0;
}
