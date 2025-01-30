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

// Drzewo przedziałowe do przechowywania sumy liczności grup
struct SegmentTree {
    vector<long long> tree;
    int size;

    SegmentTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0);
    }

    void update(int pos, int value) {
        pos += size;
        tree[pos] = value;
        while (pos > 1) {
            pos /= 2;
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
        }
    }

    long long query(int left, int right) {
        long long sum = 0;
        left += size;
        right += size;
        while (left <= right) {
            if (left % 2 == 1) sum += tree[left++];
            if (right % 2 == 0) sum += tree[right--];
            left /= 2;
            right /= 2;
        }
        return sum;
    }

    int find_first(int m) {
        // Znajduje pierwszą grupę, która może się zmieścić
        int pos = 1;
        long long sum = 0;
        if (tree[pos] < m) return -1;  // Nie ma wystarczająco osób w kolejce

        while (pos < size) {
            if (sum + tree[2 * pos] >= m) {
                pos = 2 * pos;
            } else {
                sum += tree[2 * pos];
                pos = 2 * pos + 1;
            }
        }
        return pos - size;
    }
};

int main() {
    int q;
    cin >> q;

    SegmentTree seg(MAXN);
    vector<Group> groups;
    unordered_map<int, int> index_map;  // Mapowanie ID grupy na jej pozycję w segmencie
    int group_counter = 0;

    while (q--) {
        char type;
        cin >> type;

        if (type == 'D') {
            int size, can_split;
            cin >> size >> can_split;
            ++group_counter;
            groups.push_back({group_counter, size, can_split});
            index_map[group_counter] = groups.size() - 1;
            seg.update(groups.size() - 1, size);
        } 
        else if (type == 'R') {
            int id;
            cin >> id;
            int idx = index_map[id];
            seg.update(idx, 0);  // Oznaczamy grupę jako usuniętą
        } 
        else if (type == 'P') {
            long long seats;
            cin >> seats;

            vector<pair<int, int>> result;
            long long remaining = seats;
            int idx = 0;

            while (remaining > 0) {
                int first_group = seg.find_first(remaining);
                if (first_group == -1 || first_group >= (int)groups.size()) break;

                Group &g = groups[first_group];
                if (g.size <= remaining) {
                    result.emplace_back(g.id, g.size);
                    remaining -= g.size;
                    seg.update(first_group, 0);
                } 
                else if (g.can_split) {
                    result.emplace_back(g.id, remaining);
                    g.size -= remaining;
                    seg.update(first_group, g.size);
                    remaining = 0;
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