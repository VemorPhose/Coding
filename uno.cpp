#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    
    vector<int> good;
    
    for (int r1 = 0; r1 < N; r1++) {
        for (int c1 = 0; c1 < M; c1++) {
            for (int r2 = r1 + 1; r2 < N; r2++) {
                for (int c2 = c1 + 1; c2 < M; c2++) {
                    bool isGood = true;
                    
                    for (int c = c1; c <= c2 && isGood; c++) {
                        if (grid[r1][c] != K || grid[r2][c] != K) {
                            isGood = false;
                        }
                    }
                    
                    for (int r = r1 + 1; r < r2 && isGood; r++) {
                        if (grid[r][c1] != K || grid[r][c2] != K) {
                            isGood = false;
                        }
                    }
                    
                    if (isGood) {
                        int w = c2 - c1 + 1;
                        int h = r2 - r1 + 1;
                        good.push_back(2 * w + 2 * h - 4);
                    }
                }
            }
        }
    }
    
    int tot = good.size();
    int maxLen = tot ? *max_element(good.begin(), good.end()) : 0;
    int freMax = tot ? count(good.begin(), good.end(), maxLen) : 0;
    
    cout << (tot ^ maxLen ^ freMax) << endl;
    
    return 0;
}