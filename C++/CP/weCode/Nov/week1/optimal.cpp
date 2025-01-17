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
    // int t; cin >> t;
    // while(t--){
    int n; cin >> n;
    vector<int> v;
    while(n){
        if(n>=100){
            v.pub(100);
            n-=100;
        }
        else if(n>=50){
            v.pub(50);
            n-=50;
        }
        else if(n>=20){
            v.pub(20);
            n-=20;
        }
        else if(n>=10){
            v.pub(10);
            n-=10;
        }
        else if(n>=5){
            v.pub(5);
            n-=5;
        }
        else if(n>=2){
            v.pub(2);
            n-=2;
        }
        else{
            v.pub(1);
            n--;
        }
    }

    vector<vector<int>> vBin;
    for(auto x: v){
        vector<int> temp;
        for(int i = 0; i < 8; i++){
            if(x&(1<<i)) temp.pub(1);
            else temp.pub(0);
        }
        vBin.pub(temp);
    }

    // for(int i = 0; i < 8; i++){
    //     for(int j = vBin.size() - 1; j >= 0; j--){
    //         cout << vBin[j][i] << " ";
    //     }
    //     cout << endl;
    // }

    vector<int> vOut;

    for(int i = 0; i < 8; i++){
        int temp = 0;
        for(int j = 0; j < v.size(); j++){
            temp += vBin[j][i] * (int)pow(2, v.size() - j - 1);
        }
        if(temp) vOut.pub(temp);
    }

    sort(all(vOut), greater<int>());
    for(auto x: vOut) cout << x << " ";
    cout << endl;
    // }
    return 0;
}