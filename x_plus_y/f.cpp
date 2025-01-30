#include <bits/stdc++.h>
using namespace std;

struct Group {
    int id;     // Numer grupy
    int size;   // Liczba osób w grupie
    bool canSplit; // Czy mogą się podzielić
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    deque<Group> queue;  // Kolejka grup
    unordered_map<int, bool> removed; // Lazy deletion dla usuwania grup
    int groupId = 0; // Numerowanie grup

    while (q--) {
        char type;
        cin >> type;

        if (type == 'D') {
            int z, c;
            cin >> z >> c;
            queue.push_back({++groupId, z, c == 1});
            removed[groupId] = false;  // Grupa jest aktywna
        } 
        else if (type == 'R') {
            int i;
            cin >> i;
            removed[i] = true;  // Oznaczamy grupę jako usuniętą (lazy deletion)
        } 
        else if (type == 'P') {
            int m;
            cin >> m;

            vector<pair<int, int>> result;  // Lista grup w pontonie
            while (m > 0 && !queue.empty()) {
                Group front = queue.front();
                queue.pop_front();

                if (removed[front.id]) continue; // Lazy deletion - pomijamy usunięte grupy

                if (front.size <= m) {  // Cała grupa się mieści
                    result.push_back({front.id, front.size});
                    m -= front.size;
                } else if (front.canSplit) {  // Grupa się dzieli
                    result.push_back({front.id, m});
                    queue.push_front({front.id, front.size - m, front.canSplit});
                    m = 0;
                } else {  // Grupa nie może się podzielić, zostaje w kolejce
                    queue.push_front(front);
                    break;
                }
            }

            // Wypisujemy wynik
            cout << result.size() << '\n';
            for (auto &[id, count] : result) {
                cout << id << ' ' << count << '\n';
            }
        }
    }

    return 0;
}