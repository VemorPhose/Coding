#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD int(1e9 + 7)
#define pub push_back
#define pob pop_back
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define arrIn(arr, n) for(int i = 0; i < n; i++) cin >> arr[i]

#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

int main(){
    fastio();
    string s;
    getline(cin, s);
    // cout << s << endl;
    int n = s.size() - 1;
    // cout << n << endl;
    while(s[n-1] == ' ') n--;
    char en = s[n-1];
    // cout << en << endl;
    if(en=='a'||en=='e'||en=='i'||en=='o'||en=='u'||en=='y'||en=='A'||en=='E'||en=='I'||en=='O'||en=='U'||en=='Y') cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}