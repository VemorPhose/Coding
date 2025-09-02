// 雪雁不浴自白，人亦无为而自成。
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
        ll a,b; cin>>a>>b;
        string s; cin >> s;
        ll cura = 0, curb = 0;
        ll n = a+b;
        bool flag = 1;
        for(ll i = 0; i < n/2; i++) {
            if(s[i] == s[n-1-i] && s[i] != '?') {
                if(s[i] == '0') cura += 2;
                else curb += 2;
            }
            else if((s[i] == '0' && s[n-1-i] == '1') || (s[i] == '1' && s[n-1-i] == '0')) {
                flag = 0;
                break;
            }
            else if(s[i] == '0' || s[n-1-i] == '0') {
                cura += 2;
                s[i] = '0';
                s[n-1-i] = '0';
            }
            else if(s[i] == '1' || s[n-1-i] == '1') {
                curb += 2;
                s[i] = '1';
                s[n-1-i] = '1';
            }
        }
        if(n&1) {
            if(s[n/2] == '0') cura++;
            else if(s[n/2] == '1') curb++;
            else {
                if(a&1) {
                    cura++;
                    s[n/2] = '0';
                }
                else {
                    curb++;
                    s[n/2] = '1';
                }
            }
        }

        if(!flag) cout << -1 << endl;
        else if(cura>a || curb>b) cout << -1 << endl;
        else if((a-cura)&1 || (b-curb)&1) cout << -1 << endl;
        else {
            for(ll i = 0; i < n/2; i++) {
                if(s[i] == '?' && (a-cura) > 0) {
                    s[i] = '0';
                    s[n-1-i] = '0';
                    cura += 2;
                }
                else if(s[i] == '?') {
                    s[i] = '1';
                    s[n-1-i] = '1';
                    curb += 2;
                }
            }
            cout << s << endl;
        }
    }
    return 0;
}
