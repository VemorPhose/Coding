#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int64_t
#define ull             uint64_t
#define Int             int32_t
#define uint            uint32_t
#define pii             pair<ll, ll>
#define vi              vector<ll>
#define vvi             vector<vector<ll>>
#define mpii            map<ll, ll>
#define umpii           unordered_map<ll, ll>
#define vs              vector<string>

// shortcuts
#define MOD             1000000007
#define mod             998244353
#define INF             1000000000000000010
#define PI              2 * acos(0.0)
#define LL_MAX          LLONG_MAX
#define LL_MIN          LLONG_MIN
#define ULL_MAX         ULLONG_MAX
#define endl            "\n"

// binary operations
#define swap(a,b)       a=a^b; b=b^a; a=a^b
#define setibit(n,i)    (n | (1<<i))
#define extibit(n,i)    (n & (1<<i))
#define clribit(n,i)    (n & ~(1<<i))
#define invibit(n,i)    (n ^ (1<<i))
#define setbits(x)      __builtin_popcountll(x)
#define lzbits(x)       __builtin_clzll(x)
#define tzbits(x)       __builtin_ctzll(x)

// pairs
#define ff              first
#define ss              second
#define mp              make_pair

// iterable operations
#define pub             push_back
#define pob             pop_back
#define ft              front()
#define bk              back()
#define ins             insert
#define sz(x)           (ll)x.size()
#define all(x)          (x).begin(), (x).end()

// looping
#define FOR(i, a, b)    for (int i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a)       ROF(i, 0, a)

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define arrIn(arr, n)   for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n)       for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }
#define coutN           cout << "NO" << endl
#define coutY           cout << "YES" << endl

int binarySearch(int *A, int lo, int hi, int key){
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

int primeCheck(int n){
    if(n <= 1) return 0;
    int counter, flag = 1;
    for(counter = 2; counter < n; counter++){
        if(n%counter == 0){
            flag = 0;
            break;
        }
    }
    return flag;
}

int main(){
    fastio();
    ll t; cin >> t;
    while(t--){
        int n; cin>>n;
        int arr[n]; arrIn(arr, n);
        int ta[101]; memset(ta, 0, 101*sizeof(int));
        int s[201]; memset(s, 0, 201 * sizeof(int));
        int ind1[101]; memset(ind1, -1, 101 * sizeof(int));
        int ind2[101]; memset(ind2, -1, 101 * sizeof(int));
        FOR (i, 0, n) {
            ta[arr[i]]++;
            if(ind1[arr[i]] == -1) ind1[arr[i]] = i+1;
            else ind2[arr[i]] = i+1;
        }
        
        int flag = 1;
        FOR (i, 1, 101) {
            flag = 1;
            if (ta[i] == 0) continue;
            FOR (j, (ta[i]>1?i:i+1), 101) {
                if (ta[j] == 0) continue;
                // cout << i + j << endl;
                if (!primeCheck(i + j)) {
                    if (i == j) cout << ind1[i] << " " << ind2[j] << endl;
                    else cout << ind1[i] << " " << ind1[j] << endl;
                    flag = 0;
                    break;
                }
            }
            if (!flag) break;
        }
        if (flag) cout << -1 << endl;
        // cout << endl;
    }
    return 0;
}