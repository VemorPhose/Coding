#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD int(1e9 + 7)
#define pub push_back
#define pob pop_back
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define arrIn(arr, n) for(int i = 0; i < n; i++) cin >> arr[i]

#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;



int main(){
    int t; cin >> t;
    while(t--){
        vi v;
        for(int i = 0; i < 3; i++){
            int temp; cin >> temp;
            v.pub(temp);
        }
        int counter = 0;
        sort(v.begin(), v.end());
        int num, minNum = v[0];
        num = count(v.begin(), v.end(), minNum);
        if(num == v.size()){
            cout << "YES" << endl;
            continue;
        }
        int flag = 0;
        for(int i = 0; i < 3; i++){
            v[v.size()-1] -= minNum;
            v.pub(minNum);
            sort(all(v));
            counter++;
            minNum = v[0];
            num = count(v.begin(), v.end(), minNum);
            if(num == v.size()){
                cout << "YES" << endl;
                flag = 1;
                break;
            }
        }
        if(flag == 0) cout << "NO" << endl;
    }
    return 0;
}