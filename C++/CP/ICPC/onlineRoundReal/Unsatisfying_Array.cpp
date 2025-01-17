#include <algorithm>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <utility>
#include <valarray>
#include <vector>
#include <cstring>
#include <cmath>
#include <chrono>
#include <bitset>
#include <complex>
#include <deque>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>

using namespace std;

#define BIT(i,j) (((i)>>(j))&1LL)
#define MASK(i) (1LL<<(i))
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
#define int ll
#define endl "\n"

template<typename T1, typename T2>
bool mini(T1 &a, T2 b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template<typename T1, typename T2>
bool maxi(T1 &a, T2 b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

const ll LINF = 1e18;
const int INF = 1e9;
const int MAXN = 2e3+7;
const int MOD = 1e9+7;

vector<int> add[MAXN], rem[MAXN];
int res[MAXN], cnt[MAXN];

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pii> spec;
    vector<pair<int,pii>> b;
    
    for (int i = 1; i <= k; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        b.push_back({x, {l, r}});
        // rem[l].push_back(x);
        // add[r+1].push_back(x);
    }
    
    for (int i = 1; i <= n; i++) res[i] = 1;
    sort(b.begin(), b.end());
    
    for (int i = 0; i < k; i++) {
        if (b[i].fi == n) {
            int ok = 0;
            for (int j = b[i].se.fi; j <= b[i].se.se; j++) {
                if (res[j] != n) {
                    ok = 1;
                    break;
                }
            }
            if (ok == 0) {
                cout << "-1" << endl;
                return;
            }
        } else {
            int MIN = b[i].fi;
            for (int j = b[i].se.fi; j <= b[i].se.se; j++) mini(MIN, res[j]);
            if (MIN < b[i].fi) continue;
            for (int j = b[i].se.fi; j <= b[i].se.se; j++) {
                if (res[j] == b[i].fi) {
                    res[j] = b[i].fi + 1;
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++) cout << res[i] << " ";
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    #define task "test"
    if (fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    
    int test = 1;
    cin >> test;
    for (int i = 1; i <= test; i++) solve();
    
    return 0;
}