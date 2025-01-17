#include <bits/stdc++.h>
using namespace std;
#define ll long long int

const int N = 1e7 + 10;
vector<int> g[N];
bool vis[N];
int level[N];

void bfs(vector<int>& sources) {
    queue<int> q;
    for (int vertex : sources) {
        q.push(vertex);
        vis[vertex] = 1;
    }

    while (!q.empty()) {
        int cur_v = q.front();
        q.pop();
        for (int child: g[cur_v]) {
            if (!vis[child]) {
                q.push(child);
                vis[child] = 1;
                level[child] = level[cur_v] + 1;
            }
        }
    }
}

int main(){
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int s1, s2; cin >> s1 >> s2;
    vector<int> v1;
    for (int i = 0; i < s1; i++) {
        int temp; cin >> temp;
        v1.push_back(temp);
    }
    vector<int> v2;
    for (int i = 0; i < s2; i++) {
        int temp; cin >> temp;
        v2.push_back(temp);
    }

    for (int i = 0; i < n; i++) level[i] = INT_MAX;
    for (auto x: v1) level[x] = 0;
    bfs(v1);
    int minDist = INT_MAX;
    for (auto x: v2) minDist = min(minDist, level[x]);
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (auto x: g[i]) cout << x << " ";
        cout << endl;
    }
    if (minDist == INT_MAX) cout << "d(V1, V2) = INF" << endl;
    else cout << "d(V1, V2) = " << minDist << endl;

    return 0;
}
