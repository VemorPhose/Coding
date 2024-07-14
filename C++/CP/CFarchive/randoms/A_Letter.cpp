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
    int t; cin >> t;
    while(t--){
        int m, n; cin >> m >> n;
        vector<string> vs;
        for(int i = 0; i < m; i++){
            string s; cin >> s;
            vs.pub(s);
        }
        int m1 = 0, m2 = m, n1 = 0, n2 = n;
        for(int i = 0; i < m; i++){
            int flag = 1;
            for(int j = 0; j < n; j++){
                if(vs[i][j] == '*'){
                    m1 = i;
                    flag = 0;
                    break;
                }
            }
            if(flag == 0) break;
        }
        for(int i = m-1; i >= 0; i--){
            int flag = 1;
            for(int j = 0; j < n; j++){
                if(vs[i][j] == '*'){
                    m2 = i;
                    flag = 0;
                    break;
                }
            }
            if(flag == 0) break;
        }
        for(int i = 0; i < m; i++){
            int flag = 1;
            for(int j = 0; j < n; j++){
                if(vs[j][i] == '*'){
                    n1 = i;
                    flag = 0;
                    break;
                }
            }
            if(flag == 0) break;
        }
        for(int i = 0; i < m; i++){
            int flag = 1;
            for(int j = n-1; j >= 0; j--){
                if(vs[j][i] == '*'){
                    n2 = i;
                    flag = 0;
                    break;
                }
            }
            if(flag == 0) break;
        }
        cout << m1 << m2 << n1 << n2 << endl;
        for(int i = m1; i <= m2; i++){
            for(int j = n1; j <= n2; j++){
                cout << vs[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}