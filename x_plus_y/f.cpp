#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 100;
const int MAXK = 100;

int n, k;
int skills[MAXN][MAXK];  // Umiejętności przeciwników
int gains[MAXN][MAXK];   // Przyrost umiejętności Bajtka
bool defeated[MAXN];     // Czy przeciwnik został już pokonany?

vector<int> current_skills; // Aktualne umiejętności Bajtka

// Sprawdza, czy Bajtek może pokonać przeciwnika idx
bool can_defeat(int idx) {
    for (int j = 0; j < k; j++) {
        if (current_skills[j] < skills[idx][j]) return false;
    }
    return true;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    current_skills.assign(k, 0); // Początkowe umiejętności = 0

    // Wczytanie umiejętności przeciwników
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            cin >> skills[i][j];

    // Wczytanie przyrostów umiejętności
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            cin >> gains[i][j];

    int defeated_count = 0;
    bool progress = true;

    while (progress) {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!defeated[i] && can_defeat(i)) {
                // Pokonujemy przeciwnika i aktualizujemy umiejętności
                for (int j = 0; j < k; j++) {
                    current_skills[j] += gains[i][j];
                }
                defeated[i] = true;
                defeated_count++;
                progress = true; // Restartujemy pętlę, bo Bajtek stał się silniejszy
            }
        }
    }

    cout << defeated_count << "\n";
    return 0;
}