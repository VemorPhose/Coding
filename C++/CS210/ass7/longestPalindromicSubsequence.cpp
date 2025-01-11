#include <iostream>
#include <vector>
#include <string>
using namespace std;

int longestPalindromeSubseq(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // Base case: single characters are palindromes of length 1
    for(int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // Fill the dp table
    for(int len = 2; len <= n; len++) {
        for(int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            
            if(s[i] == s[j] && len == 2) {
                dp[i][j] = 2;
            }
            else if(s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            }
            else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[0][n-1];
}

int main() {
    string test = "bbbab";
    cout << "String: " << test << endl;
    cout << "Length of Longest Palindromic Subsequence: " 
         << longestPalindromeSubseq(test) << endl;
    
    test = "cbbd";
    cout << "String: " << test << endl;
    cout << "Length of Longest Palindromic Subsequence: " 
         << longestPalindromeSubseq(test) << endl;
    
    return 0;
}