#include <bits/stdc++.h>
using namespace std;
#define ll long long int

int main(){
    ll n, m; cin >> n >> m;
    string s, t;
    if (n > 0) cin >> s;
    if (m > 0) cin >> t;
    vector<ll> scost;
    for (int i = 0; i < n; i++) {
        ll temp; cin >> temp;
        scost.push_back(temp);
    }
    vector<ll> tcost;
    for (int i = 0; i < m; i++) {
        ll temp; cin >> temp;
        tcost.push_back(temp);
    }

    if (n == 0 || m == 0) {
        cout << accumulate(scost.begin(), scost.end(), 0) + accumulate(tcost.begin(), tcost.end(), 0) << endl;
        return 0;
    }

    ll dp[n+1][m+1];
    for (int i = 0; i < n+1; i++) dp[i][0] = 0;
    for (int i = 0; i < m+1; i++) dp[0][i] = 0;

    for (int i = 1; i < n+1; i++) {
        for (int j = 1; j < m+1; j++) {
            if (s[i-1] == t[j-1]) dp[i][j] = max(max(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1] + scost[i-1] + tcost[j-1]);
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    ll totalCost = accumulate(scost.begin(), scost.end(), 0) + accumulate(tcost.begin(), tcost.end(), 0);
    totalCost = totalCost - dp[n][m];
    cout << totalCost << endl;

    return 0;
}
