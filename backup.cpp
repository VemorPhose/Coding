#include <bits/stdc++.h>
using namespace std;

string trim(string);

const int MOD = 1000000007;

int get_ans(int N, int L, int R, int X, vector<int> A) {
    vector<vector<long long>> dp(N, vector<long long>(X, 0));
    
    for (int i = 0; i < N; i++) {
        dp[i][A[i] % X] = 1;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = i + L; j <= min(i + R, N - 1); j++) {
            if (A[j] >= A[i]) {
                for (int sum = 0; sum < X; sum++) {
                    if (dp[i][sum] > 0) {
                        int new_sum = (sum + A[j]) % X;
                        dp[j][new_sum] = (dp[j][new_sum] + dp[i][sum]) % MOD;
                    }
                }
            }
        }
    }
    
    long long result = 0;
    for (int i = 0; i < N; i++) {
        result = (result + dp[i][0]) % MOD;
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string inputline;
    
    getline(cin, inputline);
    int N = stoi(trim(inputline));
    
    getline(cin, inputline);
    int L = stoi(trim(inputline));
    
    getline(cin, inputline);
    int R = stoi(trim(inputline));
    
    getline(cin, inputline);
    int X = stoi(trim(inputline));
    
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        getline(cin, inputline);
        A[i] = stoi(trim(inputline));
    }
    
    int result = get_ans(N, L, R, X, A);
    cout << result << endl;
    
    return 0;
}

string trim(string str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}