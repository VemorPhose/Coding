#include <bits/stdc++.h>
using namespace std;

string trim(string);
vector<string> splitString(string);

int max_value(int N, int K, vector<vector<int>> V) {
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(K, vector<int>(1 << K, -1)));
    
    for (int j = 0; j < K; j++) {
        dp[0][j][1 << j] = V[0][j];
    }
    
    for (int i = 1; i < N; i++) {
        for (int prev = 0; prev < K; prev++) {
            for (int mask = 0; mask < (1 << K); mask++) {
                if (dp[i-1][prev][mask] == -1) continue;
                
                for (int curr = 0; curr < K; curr++) {
                    if (curr == prev) continue;
                    
                    int new_mask = mask | (1 << curr);
                    dp[i][curr][new_mask] = max(dp[i][curr][new_mask], 
                                                dp[i-1][prev][mask] + V[i][curr]);
                }
            }
        }
    }
    
    int all_mask = (1 << K) - 1;
    int result = 0;
    
    for (int last = 0; last < K; last++) {
        if (dp[N-1][last][all_mask] == -1) continue;
        
        for (int first = 0; first < K; first++) {
            if (first == last && N > 1) continue;
            
            bool valid = false;
            for (int second = 0; second < K; second++) {
                if (N == 1 || second != first) {
                    valid = true;
                    break;
                }
            }
            if (valid) {
                result = max(result, dp[N-1][last][all_mask]);
            }
        }
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, K;
    cin >> N >> K;
    
    vector<vector<int>> V(N, vector<int>(K));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cin >> V[i][j];
        }
    }
    
    cout << max_value(N, K, V) << endl;
    
    return 0;
}

string trim(string str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> splitString(string str) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, ' ')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}