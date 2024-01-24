// made by Vemor Phose
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int64_t
#define ull             uint64_t
#define int             int32_t
#define uint            uint32_t

// shortcuts
#define endl            "\n"

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define arrIn(arr, n)   for(ll i = 0; i < n; i++) cin >> arr[i]

int main(){
    fastio();
    // 1
    int n; cin >> n;
    int arr[n]; arrIn(arr, n);

    // 2
    int cntarr[100010];
    memset(cntarr, 0, sizeof(cntarr));

    // 3
    for(auto x: arr) cntarr[x]++;
    
    // 4
    int cnt = 0;
    for(int i = 0; i < 100010 && cnt <= n; i++){
        for(int j = 0; j < cntarr[i]; j++){
            arr[cnt++] = i;
        }
    }

    // 5
    for(auto x: arr) cout << x << " ";
    cout << endl;

    return 0;
}

/*-------TIME COMPLEXITY ANALYSIS------*/
// let N = 1e7, M = 1e5;
// 1 --> O(N);
// 2 --> O(M);
// 3 --> O(N);
// 4 --> net operations will not exceed N => O(N);
// 5 --> O(N);
// Overall: O(4*N) ~~ O(N)