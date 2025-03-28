#include <iostream>
#include <vector>
using namespace std;

const long long MAXN = 1e6 + 7;
long long now[MAXN];
long long req[MAXN];
vector<long long> graph[MAXN];
vector<long long> graph2[MAXN];
bool visited[MAXN];
long long prefRight[MAXN];
long long prefLeft[MAXN];
long long wait[MAXN];
long long res = 0;

void dfs(long long s) {
    visited[s] = true;
    for (auto v : graph[s]) {
        if (!visited[v]) {
            if (now[s] == 0) {
                wait[v] = max(wait[s] + 1, wait[s] - (now[v] - req[v]));
            } else if (now[s] - req[s] < 0) {
                wait[v] = wait[s] - (now[s] - req[s]);
            } else {
                wait[v] = wait[s];
            }
        }
        long long dif = now[v] - req[v];
        if (graph2[v].size() == 2) {
            long long g = graph2[v][0];
            long long right = 0;
            while (!graph2[g].empty()) {
                right += (now[g] - req[g]);
                g = graph2[g][0];
            }
            right += (now[g] - req[g]);
            g = graph2[v][1];
            long long left = 0;
            while (!graph2[g].empty()) {
                left += (now[g] - req[g]);
                g = graph2[g][0];
            }
            left += (now[g] - req[g]);
            dif = -max(right, left);
        }
        res = max(res, -dif + wait[v]);
        dfs(v);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long n;
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        cin >> now[i];
    }
    prefLeft[0] = 0;
    for (long long i = 1; i <= n; i++) {
        cin >> req[i];
        prefLeft[i] = prefLeft[i - 1] + now[i] - req[i];
        prefRight[i] = -prefLeft[i - 1];
    }

    for (long long i = 1; i <= n; i++) {
        long long curr;
        if (prefLeft[i] == 0 && prefRight[i] <= 0) {
            continue;
        }
        if (prefLeft[i] > 0 && prefRight[i] >= 0) {
            curr = 1;
        }
        if (prefLeft[i] < 0 && prefRight[i] <= 0) {
            curr = -1;
            continue;
        }
        graph[i].push_back(i + curr);
        graph2[i + curr].push_back(i);
    }

    for (long long i = 1; i <= n; i++) {
        if (graph2[i].empty()) {
            dfs(i);
        }
    }

    cout << res;
}