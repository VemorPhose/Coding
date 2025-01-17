#include <iostream>
#include <vector>
using namespace std;

int timeRequired(int N, int M, vector<int> T, vector<int> F) {
    if (M == 0) return 0;
    
    // Calculate processing time for each worker-laptop combination
    vector<vector<int>> protime(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            protime[i][j] = T[i] * F[j];
        }
    }
    
    // Initialize start times for each laptop
    vector<long long> st(M, 0);  // Using long long to prevent overflow
    
    // For each laptop after the first one
    for (int j = 1; j < M; j++) {
        // Initialize minimum start time as start time of previous laptop
        long long mst = st[j-1];
        
        // Check constraints with previous laptop
        for (int i = 0; i < N; i++) {
            // Calculate when worker i finishes with previous laptop
            long long wpf = st[j-1];
            for (int k = 0; k <= i; k++) {
                wpf += protime[k][j-1];
            }
            
            // Calculate time accumulated before reaching worker i for current laptop
            long long caa = 0;
            for (int k = 0; k < i; k++) {
                caa += protime[k][j];
            }
            
            // Current laptop must wait until worker is available
            long long rqw = wpf - caa;
            mst = max(mst, rqw);
        }
        
        st[j] = mst;
    }
    
    // Calculate total completion time
    long long tt = st[M-1];
    for (int i = 0; i < N; i++) {
        tt += protime[i][M-1];
    }
    
    return static_cast<int>(tt);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Read N and M
    int N, M;
    cin >> N >> M;
    
    // Read worker times
    vector<int> T(N);
    for(int i = 0; i < N; i++) {
        cin >> T[i];
    }
    
    // Read laptop complexity factors
    vector<int> F(M);
    for(int i = 0; i < M; i++) {
        cin >> F[i];
    }
    
    // Calculate and print result
    int result = timeRequired(N, M, T, F);
    cout << result << endl;
    
    return 0;
}