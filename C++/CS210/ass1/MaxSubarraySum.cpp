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

int main(){
    fastio();
    int n; cin >> n;
    int arr[n]; arrIn(arr, n);

    // kadane algorithm

    int maxSum = arr[0], curSum = arr[0];
    FOR (i, 1, n) {
        if (curSum > maxSum) maxSum = curSum;
        if (curSum < 0) curSum = 0;
        curSum += arr[i];
    }
    if (curSum > maxSum) maxSum = curSum;

    cout << maxSum << endl;

    return 0;
}

/* try prefix sum
max sum = max element of prefix array - min element of prefix array strictly to the left of max element index
UPDATE: doesn't work. Rather I couldnt make it work. It does work for a lot of testcases though.

    // prefix sum approach

    int arrPrefix[n];
    arrPrefix[0] = arr[0];
    int maxIndex = 0;
    bool negFlag = 1;
    for (auto x: arr) if (x > 0) negFlag = 0;
    FOR (i, 1, n) {
        arrPrefix[i] = arrPrefix[i-1] + arr[i];
        if (arrPrefix[i] >= arrPrefix[maxIndex]) maxIndex = i;
    }

    int min = 0, minIndex = -1;
    FOR (i, 0, maxIndex) {
        if (arrPrefix[i] < min) {
            min = arrPrefix[i];
            minIndex = i;
        }
    }

    for (auto x: arrPrefix) cout << x << " ";
    cout << endl;

    int maxSubarraySum = (maxIndex == minIndex ? arrPrefix[maxIndex] : (arrPrefix[maxIndex] - min));
    if (negFlag) {
            int maxElement = INT_MIN;
            for (auto x: arr) if (x > maxElement) maxElement = x;
            cout << maxElement << endl;
        }
    else cout << maxSubarraySum << endl;
*/