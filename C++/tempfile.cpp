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
    fastio();
    int t; cin >> t;
    while(t--){
        int n;cin>>n;
        std::vector<int> v;
        for(int i = 0; i < n; i++){
            int temp; cin>>temp;v.pub(temp);
        }
        
		int maxIndex = (max_element(all(v)) - v.begin());
        // cout << maxIndex << endl;

		int buf = v[0], sum = buf;
		for(int i = 1; i <= maxIndex; i++){
			if(v[i] < buf) sum += buf;
			else{
				buf = v[i];
				sum += buf;
			}
		}
		buf = 0;
		for(int i = n-1; i > maxIndex; i--){
			if(v[i] < buf) sum += buf;
			else{
				buf = v[i];
				sum += buf;
			}
		}
        // int total = accumulate(all(v), 0);
        // cout << total << endl;

		// for(auto i: v) cout << i << ' ';
		cout << sum << endl;
    }
    return 0;
}