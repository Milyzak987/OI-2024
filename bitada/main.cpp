#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 3000 + 1;
int n, m, k;
vector<int> treeBitada[MAXN], treeBajtogrod[MAXN];
int dp[MAXN][MAXN];

// Funkcja DFS do obliczenia liczby możliwych przypisań poddrzew Bitady do Bajtogrodu
int calculate(int u, int v, int parentU, int parentV) {
    // Jeśli już obliczono wynik dla u -> v, zwróć go
    if (dp[u][v] != -1) return dp[u][v];
    
    // Liczba sposobów przypisań poddrzew u w Bitadzie do poddrzewa v w Bajtogrodzie
    int ways = 1;

    // Zbierz dzieci węzła u w Bitadzie i v w Bajtogrodzie
    vector<int> childrenU, childrenV;
    for (int child : treeBitada[u]) {
        if (child != parentU) childrenU.push_back(child);
    }
    for (int child : treeBajtogrod[v]) {
        if (child != parentV) childrenV.push_back(child);
    }

    // Jeśli liczba dzieci węzła u jest większa niż liczba dzieci węzła v, zwróć 0
    if (childrenU.size() > childrenV.size()) return dp[u][v] = 0;

    // Używamy DP, aby przeliczyć możliwe przypisania dzieci u do dzieci v
    vector<vector<int>> childDP(childrenU.size() + 1, vector<int>(childrenV.size() + 1, 0));
    childDP[0][0] = 1;

    for (int i = 0; i <= childrenU.size(); ++i) {
        for (int j = 0; j <= childrenV.size(); ++j) {
            if (childDP[i][j] == 0) continue;

            if (i < childrenU.size() && j < childrenV.size()) {
                int possibleWays = calculate(childrenU[i], childrenV[j], u, v);
                childDP[i + 1][j + 1] = (childDP[i + 1][j + 1] + 1LL * childDP[i][j] * possibleWays % k) % k;
            }

            if (j < childrenV.size()) {
                childDP[i][j + 1] = (childDP[i][j + 1] + childDP[i][j]) % k;
            }
        }
    }

    // Wynik dla dp[u][v] to liczba sposobów na przypisanie wszystkich dzieci u do dzieci v
    ways = childDP[childrenU.size()][childrenV.size()];

    return dp[u][v] = ways;
}

int main() {
    cin >> n >> m >> k;

    // Inicjalizuj drzewa
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        treeBitada[x].push_back(y);
        treeBitada[y].push_back(x);
    }

    for (int i = 0; i < m - 1; ++i) {
        int x, y;
        cin >> x >> y;
        treeBajtogrod[x].push_back(y);
        treeBajtogrod[y].push_back(x);
    }

    // Inicjalizacja dp
    memset(dp, -1, sizeof(dp));

    // Liczymy wynik dla przypisania wierzchołka 1 w Bitadzie do każdego wierzchołka w Bajtogrodzie
    int result = 0;
    for (int v = 1; v <= m; ++v) {
        result = (result + calculate(1, v, -1, -1)) % k;
    }

    cout << result << endl;
    return 0;
}
