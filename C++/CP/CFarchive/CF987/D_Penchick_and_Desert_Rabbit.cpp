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
#define FOR(i, a, b)    for (ll i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a)       ROF(i, 0, a)

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define arrIn(arr, n)   for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n)       for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }
#define coutN           cout << "NO" << endl
#define coutY           cout << "YES" << endl

int main(){
    fastio();
    ll t; cin >> t;
    while(t--){
        int n;
        cin >> n;
        int a[n];
        for(int i=0; i<n; i++)
        {
            cin >> a[i];
        }

        int mx[n];
        int high = -1;
        for(int i=0; i<n; i++)
        {
            if(a[i]>high)
            {
                high = a[i];
            }
            mx[i] = high;
            //cout << mxm[i] << " ";
        }
        //cout << endl;
        for(int i=0; i<n; i++)
        {
            cout << mx[i] << " ";
        }
        cout << endl;


        int mn[n];
        mn[n-1] = n-1;
        for(int i=n-1; i>=0; i--)
        {
            int bareMin = i;
            int l=i+1; int r=n-1;
            while(l<=r)
            {
                int mid = (l+r)/2;
                if(mn[mid] <= a[i])
                {
                    bareMin = mid;
                    l = mid+1;
                }
                if(mn[mid]>a[i])
                {
                    r = mid-1;
                }
            }
            mn[i] = bareMin;
            cout << mn[i] << " ";
        }

        /*for(int i=0; i<n; i++)
        {
            int first = mx[i];
            int second = mx[mn[i]];
            cout << first << " " << second << endl;
            if(first>=second)
                cout << first << " ";
            else
                cout << second << " ";
            cout << endl;
        }*/
        cout << endl;
        
    }
    
    return 0;
}
