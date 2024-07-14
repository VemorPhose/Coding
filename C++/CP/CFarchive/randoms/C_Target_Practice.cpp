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
        vector<string> vs;
        int pts = 0;
        for(int i = 0; i < 10; i++){
            string s; cin >> s;
            for(int j = 0; j < 10; j++){
                if(s[j] == 'X'){
                    if(i==0||i==9){
                        pts++;
                    }
                    else if(i==1||i==8){
                        if(j==0||j==9) pts++;
                        else pts+=2;
                    }
                    else if(i==2||i==7){
                        if(j==0||j==9) pts++;
                        else if(j==1||j==8) pts+=2;
                        else pts+=3;
                    }
                    else if(i==3||i==6){
                        if(j==0||j==9) pts++;
                        else if(j==1||j==8) pts+=2;
                        else if(j==2||j==7) pts+=3;
                        else pts+=4;
                    }
                    else if(i==4||i==5){
                        if(j==0||j==9) pts++;
                        else if(j==1||j==8) pts+=2;
                        else if(j==2||j==7) pts+=3;
                        else if(j==3||j==6) pts+=4;
                        else pts+=5;
                    }
                }
            }
        }
        cout << pts << endl;
    }
    return 0;
}