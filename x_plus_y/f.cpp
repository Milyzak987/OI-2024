#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> solve(int n, int m, int q, const vector<pair<int, int>>& tasks, const vector<long long>& queries) {
    vector<int> machine_order;  // Kolejność uruchamiania maszyn

    // Generowanie kolejności maszyn
    for (const auto& task : tasks) {
        for (int i = task.first; i <= task.second; ++i) {
            machine_order.push_back(i);
        }
    }

    int total_days = machine_order.size();
    vector<int> results(q, 0);  // Wyniki dla zapytań

    // Obsługa zapytań
    for (int qi = 0; qi < q; ++qi) {
        long long s = queries[qi];
        vector<int> last_used(n + 1, -1);  // Ostatni dzień użycia każdej maszyny
        int inspection_count = 0;

        for (int day = 0; day < total_days; ++day) {
            int machine = machine_order[day];
            if (last_used[machine] != -1 && day - last_used[machine] > s) {
                ++inspection_count;
            }
            last_used[machine] = day;
        }

        results[qi] = inspection_count;
    }

    return results;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Wczytywanie danych wejściowych
    int n, m, q;
    cin >> n >> m >> q;

    vector<pair<int, int>> tasks(m);
    for (int i = 0; i < m; ++i) {
        cin >> tasks[i].first >> tasks[i].second;
    }

    vector<long long> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
    }

    // Wywołanie funkcji rozwiązującej
    vector<int> result = solve(n, m, q, tasks, queries);

    // Wyświetlenie wyników
    for (int res : result) {
        cout << res << " ";
    }
    cout << "\n";

    return 0;
}