#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

const int MAXN = 200005;

vector<int> graph[MAXN];
bool removed[MAXN]; // Czy dany wierzchołek został usunięty
int subtree_size[MAXN];
vector<int> depths;

// Oblicz rozmiary poddrzew
int calculate_subtree_sizes(int v, int parent) {
    subtree_size[v] = 1;
    for (int u : graph[v]) {
        if (u != parent && !removed[u]) {
            subtree_size[v] += calculate_subtree_sizes(u, v);
        }
    }
    return subtree_size[v];
}

// Znajdź centroid
int find_centroid(int v, int parent, int total_size) {
    for (int u : graph[v]) {
        if (u != parent && !removed[u] && subtree_size[u] > total_size / 2) {
            return find_centroid(u, v, total_size);
        }
    }
    return v;
}

// Oblicz głębokości z centroidu
void calculate_depths(int v, int parent, int depth) {
    depths.push_back(depth);
    for (int u : graph[v]) {
        if (u != parent && !removed[u]) {
            calculate_depths(u, v, depth + 1);
        }
    }
}

// Dekompozycja centroidowa
int centroid_decomposition(int v) {
    // Znajdź rozmiar poddrzewa
    int total_size = calculate_subtree_sizes(v, -1);
    // Znajdź centroid
    int centroid = find_centroid(v, -1, total_size);
    removed[centroid] = true;

    // Przetwarzaj centroid
    vector<int> all_depths = {0}; // Dodajemy głębokość centroidu
    for (int u : graph[centroid]) {
        if (!removed[u]) {
            depths.clear();
            calculate_depths(u, centroid, 1);
            all_depths.insert(all_depths.end(), depths.begin(), depths.end());
        }
    }

    // Posortuj głębokości i wybierz optymalne
    sort(all_depths.begin(), all_depths.end(), greater<int>());
    int result = all_depths.size() > k ? all_depths[k] : 0;

    // Rekurencyjnie dekomponuj poddrzewa
    for (int u : graph[centroid]) {
        if (!removed[u]) {
            result = min(result, centroid_decomposition(u));
        }
    }

    removed[centroid] = false; // Przywróć stan
    return result;
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

    // Rozpocznij dekompozycję
    cout << centroid_decomposition(1) << "\n";

    return 0;
}