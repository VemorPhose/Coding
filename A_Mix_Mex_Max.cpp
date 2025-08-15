int binarySearch(vector<int> A, int lo, int hi, int key){
    if(hi == lo){
        if(A[lo] == key)
            return lo;
        return -1;
    }
    int mid = (lo+hi)/2;
    if(A[mid] >= key)
        return binarySearch(A, lo, mid, key);
    else
        return binarySearch(A, mid+1, hi, key);
}

const int N = 1e7 + 10;
vector<bool> primes(N, 1);

void sieve() {
    primes[0] = primes[1] = 0;
    for (int i = 2; i < N; i++) {
        if (primes[i]) {
            for (int j = i + i; j < N; j += i) {
                primes[j] = 0;
            }
        }
    }
}

const int N = 1e7 + 10;
vector<int> g[N];
bool vis[N];

void dfs(int vertex) {
    // Take action on vertex after entering the vertex
    vis[vertex] = 1;
    for (int child: g[vertex]) {
        if (vis[child]) continue;
        // Take action on child before entering the child node
        dfs(child);
        // Take action on child after exiting the child node
    }
    // Take action on vertex before exiting the vertex
    return;
}

int level[N];

void bfs(int vertex) {
    queue<int> q;
    q.push(vertex);
    vis[vertex] = 1;
    level[vertex] = 0;

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

// cut-paste in main
    int v, e; cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int v1, v2; cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }