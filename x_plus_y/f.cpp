#include <bits/stdc++.h>
using namespace std;

ios_base::sync_with_stdio(0);
cin.tie(0);

const int MAXN = 2e5 + 7;
vector<int> graph[MAXN];

struct Group {
    int id, size;
    bool can_split;
};

queue<Group> q;
unordered_map<int, Group> active_groups;
int group_counter = 0;

int main() {
    int query_count;
    cin >> query_count;

    while (query_count--) {
        char type;
        cin >> type;

        if (type == 'D') {
            int size, can_split;
            cin >> size >> can_split;
            ++group_counter;
            Group new_group = {group_counter, size, can_split};
            q.push(new_group);
            active_groups[group_counter] = new_group;
        } 
        else if (type == 'R') {
            int id;
            cin >> id;
            active_groups.erase(id);
        } 
        else if (type == 'P') {
            long long seats;
            cin >> seats;
            
            vector<pair<int, int>> result;
            
            while (!q.empty() && seats > 0) {
                Group current = q.front();
                if (active_groups.find(current.id) == active_groups.end()) {
                    q.pop();
                    continue;
                }

                if (current.size <= seats) {
                    result.emplace_back(current.id, current.size);
                    seats -= current.size;
                    q.pop();
                    active_groups.erase(current.id);
                } 
                else if (current.can_split) {
                    result.emplace_back(current.id, seats);
                    active_groups[current.id].size -= seats;
                    seats = 0;
                } 
                else {
                    break;
                }
            }

            cout << result.size() << '\n';
            for (auto &[id, count] : result) {
                cout << id << ' ' << count << '\n';
            }
        }
    }

    return 0;
}