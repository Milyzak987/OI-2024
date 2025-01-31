#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Opponent {
    vector<int> skills;
    vector<int> gains;
};

// Funkcja sprawdzająca, czy Bajtek może pokonać przeciwnika
bool can_defeat(const vector<int> &current_skills, const Opponent &opponent, int k) {
    for (int j = 0; j < k; j++) {
        if (current_skills[j] < opponent.skills[j]) return false;
    }
    return true;
}

// Sortowanie przeciwników według ich najtrudniejszej karty
bool compare(const Opponent &a, const Opponent &b) {
    return *max_element(a.skills.begin(), a.skills.end()) < *max_element(b.skills.begin(), b.skills.end());
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<Opponent> opponents(n);
    vector<int> current_skills(k, 0); // Początkowe umiejętności Bajtka

    // Wczytanie umiejętności przeciwników
    for (int i = 0; i < n; i++) {
        opponents[i].skills.resize(k);
        for (int j = 0; j < k; j++) {
            cin >> opponents[i].skills[j];
        }
    }

    // Wczytanie przyrostów umiejętności
    for (int i = 0; i < n; i++) {
        opponents[i].gains.resize(k);
        for (int j = 0; j < k; j++) {
            cin >> opponents[i].gains[j];
        }
    }

    // Sortujemy przeciwników według trudności
    sort(opponents.begin(), opponents.end(), compare);

    int defeated = 0;

    // Przechodzimy przez posortowanych przeciwników i sprawdzamy, czy Bajtek ich pokona
    for (const auto &opponent : opponents) {
        if (can_defeat(current_skills, opponent, k)) {
            // Aktualizacja umiejętności Bajtka
            for (int j = 0; j < k; j++) {
                current_skills[j] += opponent.gains[j];
            }
            defeated++;
        }
    }

    cout << defeated << "\n";
    return 0;
}