#include <bits/stdc++.h>
using namespace std;

int countOnes(int N, int M, vector<int> Pos) {
    vector<int> A(N + 1, 0);
    set<int> robots;
    
    for (int i = 0; i < M; i++) {
        int x = Pos[i];
        robots.erase(x);
        robots.insert(x);
        vector<int> robotList(robots.begin(), robots.end());
        
        for (int j = 0; j < (int)robotList.size() - 1; j++) {
            int start = robotList[j];
            int end = robotList[j + 1];
            for (int k = start; k <= end; k++) {
                A[k] = 1 - A[k];
            }
        }
    }
    
    int result = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] == 1) {
            result++;
        }
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int N, M;
    cin >> N >> M;
    
    vector<int> Pos(M);
    for (int i = 0; i < M; i++) {
        cin >> Pos[i];
    }
    
    cout << countOnes(N, M, Pos) << endl;
    
    return 0;
}