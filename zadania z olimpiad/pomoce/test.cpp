#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> Pair;

const int MAXN = 1e5 + 7;
const int INF = 2e9;
vector<Pair> graph[MAXN];
vector<int> graph2[MAXN];
vector<int> dist(MAXN, INF);
vector<int> arr(MAXN);
vector<bool> visited(MAXN);

void dijkstra(int s){
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while(!pq.empty()){
        int v = pq.top().second;
        pq.pop();
        for(auto p : graph[v]){
            int u = p.first;
            int w = p.second;
            if(dist[u] > dist[v] + w){
                dist[u] = dist[v] + w;
                pq.push({dist[u], u});
            }
        }
    }
}

int binsearch(int l, int r, int x){
    while(l < r){
        int mid = (l + r) / 2;
        if(arr[mid] >= x){
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

void dfs(int v){
    visited[v] = true;
    for(auto x : graph2[v]){
        if(!visited[x]){
            dfs(x);
        }
    }
}

int gasienica(int n, int x){
    int glowa = 0, ogon = 0, res = INF, curr = 0;
    while(glowa < n){
        glowa++;
        curr += arr[glowa];
        if(curr < x){
            continue;
        }
        if(curr == x){
            res = min(res, glowa - ogon + 1);
        }
        while(ogon < glowa && curr > x){
            curr -= arr[ogon];
            ogon++;
            if(curr == x){
                res = min(res, glowa - ogon + 1);
            }
        }
    }
}

void bfs(int u){
    queue<int> q;
    dist[u] = 0;
    q.push(u);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto u : graph2[v]){
            if(dist[u] == -1){
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }
}