#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 200000;
vector<int> graph[MAX_N + 1];  // Lista sąsiedztwa
int in_degree[MAX_N + 1];       // Stopnie wejściowe
int result[MAX_N + 1];          // Wyniki dla każdego gracza
int last_match[MAX_N + 1];      // Ostatni mecz, po którym określono rangę

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Wczytanie meczów i budowanie grafu
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[y].push_back(x);
        in_degree[x]++;
    }

    // Kolejka do BFS (sortowanie topologiczne)
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
            last_match[i] = 0; // Gracze bez przegranych są określeni od początku
        } else {
            last_match[i] = -1; // Domyślnie ustawiamy jako nieokreślony
        }
    }

    int matches_played = 0;
    while (!q.empty()) {
        matches_played++; // Liczymy, po ilu meczach znamy rangę
        int size = q.size();
        vector<int> current_nodes;

        for (int i = 0; i < size; i++) {
            int node = q.front();
            q.pop();
            current_nodes.push_back(node);
        }

        for (int node : current_nodes) {
            result[node] = matches_played; // Zapisujemy moment określenia rangi
            for (int neighbor : graph[node]) {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0) {
                    q.push(neighbor);
                    last_match[neighbor] = matches_played;
                }
            }
        }
    }

    // Wypisanie wyniku
    for (int i = 1; i <= n; i++) {
        cout << last_match[i] << " ";
    }
    cout << "\n";

    return 0;
}