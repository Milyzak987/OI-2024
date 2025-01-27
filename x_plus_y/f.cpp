#include <iostream>
#include <cstring> // Do użycia memset
using namespace std;

const int MAXN = 2e5 + 7; // Maksymalna liczba maszyn/dni
const int MAXQ = 2e5 + 7; // Maksymalna liczba zapytań

// Globalne tablice
int machine_order[MAXN];  // Kolejność uruchamiania maszyn
int last_used[MAXN];      // Ostatni dzień użycia maszyn
int results[MAXQ];        // Wyniki zapytań
pair<int, int> tasks[MAXN]; // Zakresy zadań
long long queries[MAXQ];  // Wartości bezpieczeństwa S

void solve(int n, int m, int q) {
    int total_days = 0;

    // Generowanie kolejności maszyn
    for (int i = 0; i < m; ++i) {
        for (int j = tasks[i].first; j <= tasks[i].second; ++j) {
            machine_order[total_days++] = j;
        }
    }

    // Obsługa zapytań
    for (int qi = 0; qi < q; ++qi) {
        long long s = queries[qi];

        // Resetowanie tablicy `last_used`
        memset(last_used, -1, sizeof(last_used));

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
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Wczytywanie danych wejściowych
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < m; ++i) {
        cin >> tasks[i].first >> tasks[i].second;
    }

    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
    }

    // Wywołanie funkcji rozwiązującej
    solve(n, m, q);

    // Wyświetlenie wyników
    for (int i = 0; i < q; ++i) {
        cout << results[i] << " ";
    }
    cout << "\n";

    return 0;
}