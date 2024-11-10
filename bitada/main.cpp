// jak ktos to czytasz to z gory przepraszam
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 3007;
int n, m, k;
vector<int> bitin[MAXN], bitada[MAXN], bajtogrod[MAXN];
long long dp[MAXN][MAXN][4];
bool visited[MAXN];

int nodeToNum(int targetChild, int parent) {
    if (bajtogrod[parent][0] == targetChild) {
        return 0;
    }
    if (bajtogrod[parent][1] == targetChild) {
        return 1;
    }
    if (bajtogrod[parent][2] == targetChild) {
        return 2;
    }
    return 3;
}

void graphToTree(int v) {
    visited[v] = true;
    for (auto x : bitin[v]) {
        if (!visited[x]) {
            bitada[v].push_back(x);
            graphToTree(x);
        }
    }
}

long long countUtoV(int v, int u, int edge) {
    if (dp[v][u][edge] == -1) {
        int chu = bitada[u].size();
        int chv;
        if (edge == 3) {
            chv = bajtogrod[v].size();
        } else {
            chv = bajtogrod[v].size() - 1;
        }

        if (chu == 0) {
            dp[v][u][edge] = 1;
            return dp[v][u][edge];
        }
        if (chu > chv) {
            dp[v][u][edge] = 0;
            return dp[v][u][edge];
        }

        int chv1, chv2, chv3, chu1, chu2;
        // wiem ze te ify sa brzydkie nie musisz mi o tym przypominac
        if (edge == 0) {
            chv1 = bajtogrod[v][min(chv, 1)];
            chv2 = bajtogrod[v][min(chv, 2)];
        }
        if (edge == 1) {
            chv1 = bajtogrod[v][min(chv, 0)];
            chv2 = bajtogrod[v][min(chv, 2)];
        }
        if (edge == 2) {
            chv1 = bajtogrod[v][min(chv, 0)];
            chv2 = bajtogrod[v][min(chv, 1)];
        }
        if (edge == 3) {
            chv1 = bajtogrod[v][min(chv - 1, 0)];
            chv2 = bajtogrod[v][min(chv - 1, 1)];
            chv3 = bajtogrod[v][min(chv - 1, 2)];
        }
        chu1 = bitada[u][0];
        chu2 = bitada[u][1];

        if (chv == 1 && chu == 1) {
            dp[v][u][edge] = (countUtoV(chv1, chu1, nodeToNum(v, chv1))) % k;
        }
        if (chv == 2 && chu == 1) {
            dp[v][u][edge] = (countUtoV(chv1, chu1, nodeToNum(v, chv1)) +
                              countUtoV(chv2, chu1, nodeToNum(v, chv2))) %
                             k;
        }
        if (chv == 2 && chu == 2) {
            dp[v][u][edge] = (((countUtoV(chv1, chu1, nodeToNum(v, chv1)) *
                                countUtoV(chv2, chu2, nodeToNum(v, chv2))) %
                               k) +
                              ((countUtoV(chv1, chu2, nodeToNum(v, chv1)) *
                                countUtoV(chv2, chu1, nodeToNum(v, chv2))) %
                               k)) %
                             k;
        }
        if (chv == 3 && chu == 1) {
            dp[v][u][edge] = (countUtoV(chv1, chu1, nodeToNum(v, chv1)) +
                              countUtoV(chv2, chu1, nodeToNum(v, chv2)) +
                              countUtoV(chv3, chu1, nodeToNum(v, chv3))) %
                             k;
        }
        if (chv == 3 && chu == 2) {
            // naprawde przepraszam, wiem ze mozna zrobic to lepiej,
            // ale jak cos dziala to lepiej tego nie ruszac
            dp[v][u][edge] = (((countUtoV(chv1, chu1, nodeToNum(v, chv1)) *
                                countUtoV(chv2, chu2, nodeToNum(v, chv2))) %
                               k) +
                              ((countUtoV(chv1, chu1, nodeToNum(v, chv1)) *
                                countUtoV(chv3, chu2, nodeToNum(v, chv3))) %
                               k) +
                              ((countUtoV(chv2, chu1, nodeToNum(v, chv2)) *
                                countUtoV(chv1, chu2, nodeToNum(v, chv1))) %
                               k) +
                              ((countUtoV(chv2, chu1, nodeToNum(v, chv2)) *
                                countUtoV(chv3, chu2, nodeToNum(v, chv3))) %
                               k) +
                              ((countUtoV(chv3, chu1, nodeToNum(v, chv3)) *
                                countUtoV(chv1, chu2, nodeToNum(v, chv1))) %
                               k) +
                              ((countUtoV(chv3, chu1, nodeToNum(v, chv3)) *
                                countUtoV(chv2, chu2, nodeToNum(v, chv2))) %
                               k)) %
                             k;
        }
    } else {
        return dp[v][u][edge];
    }
    return dp[v][u][edge];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        bitin[x].push_back(y);
        bitin[y].push_back(x);
    }

    int root;
    for (int i = 1; i <= n; ++i) {
        if (bitin[i].size() < 3) {
            root = i;
            break;
        }
    }

    graphToTree(root);

    for (int i = 0; i < m - 1; ++i) {
        int x, y;
        cin >> x >> y;
        bajtogrod[x].push_back(y);
        bajtogrod[y].push_back(x);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = 0; l < 4; l++) {
                dp[i][j][l] = -1;
            }
        }
    }

    int result = 0;
    for (int v = 1; v <= m; ++v) {
        result = (result + countUtoV(v, root, 3)) % k;
    }

    cout << result;
    // tak wiem ze mozna to zrobic szybciej, ladniej i z użyciem mniejszej ilosci pamieci,
    // ale wynik jest dobry i wchodzi na 100 (hopefully), wiec nie moge narzekac
    return 0;
}
