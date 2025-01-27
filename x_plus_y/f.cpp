#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// Funkcja przetwarzająca zadanie
vector<int> solve(int n, int m, int q, vector<pair<int, int>> tasks, vector<long long> queries) {
    vector<int> machine_order;  // Kolejność uruchamiania maszyn
    
    // Generowanie kolejności maszyn
    for (auto &[l, r] : tasks) {
        for (int i = l; i <= r; ++i) {
            machine_order.push_back(i);
        }
    }
    
    int total_days = machine_order.size();
    vector<long long> last_used(n + 1, -1);  // Ostatni dzień użycia maszyny
    vector<long long> inspections(total_days + 1, 0);  // Liczba inspekcji do dnia t

    // Obliczanie liczby inspekcji dla wszystkich dni
    for (int i = 0; i < total_days; ++i) {
        int machine = machine_order[i];
        if (last_used[machine] != -1) {
            inspections[i + 1] = inspections[i] + (i - last_used[machine] > 0);
        } else {
            inspections[i + 1] = inspections[i];
        }
        last_used[machine] = i;
    }

    // Przetwarzanie zapytań
    vector<int> results;
    for (long long s : queries) {
        if (s >= total_days) {
            results.push_back(0);
        } else {
            results.push_back(inspections[total_days] - inspections[s]);
        }
    }

    return results;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

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

    vector<int> result = solve(n, m, q, tasks, queries);

    for (int res : result) {
        cout << res << " ";
    }
    cout << "\n";

    return 0;
}