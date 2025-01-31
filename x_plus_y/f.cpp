#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1000006; // Maksymalna wielkość danych

int n, k;
int skills[MAXN][MAXN];  // Umiejętności przeciwników
int gains[MAXN][MAXN];   // Przyrost umiejętności Bajtka
int current_skills[MAXN]; // Aktualne umiejętności Bajtka
int order[MAXN];         // Indeksy przeciwników po sortowaniu

// Funkcja sprawdzająca, czy Bajtek może pokonać przeciwnika
bool can_defeat(int idx) {
    for (int j = 0; j < k; j++) {
        if (current_skills[j] < skills[idx][j]) return false;
    }
    return true;
}

// Sortowanie przeciwników według ich najtrudniejszej karty
bool compare(int a, int b) {
    return *max_element(skills[a], skills[a] + k) < *max_element(skills[b], skills[b] + k);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    // Wczytanie umiejętności przeciwników
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> skills[i][j];
        }
    }

    // Wczytanie przyrostów umiejętności
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> gains[i][j];
        }
    }

    // Inicjalizacja początkowych umiejętności Bajtka
    fill(current_skills, current_skills + k, 0);

    // Inicjalizacja indeksów przeciwników
    for (int i = 0; i < n; i++) order[i] = i;

    // Sortujemy przeciwników według trudności
    sort(order, order + n, compare);

    int defeated = 0;

    // Przechodzimy przez posortowanych przeciwników i sprawdzamy, czy Bajtek ich pokona
    for (int i = 0; i < n; i++) {
        int idx = order[i];
        if (can_defeat(idx)) {
            // Aktualizacja umiejętności Bajtka
            for (int j = 0; j < k; j++) {
                current_skills[j] += gains[idx][j];
            }
            defeated++;
        }
    }

    cout << defeated << "\n";
    return 0;
}