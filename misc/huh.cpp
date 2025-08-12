#include <bits/stdc++.h>
using namespace std;

int minimumCost(vector<int>& A, int B) {
    int N = A.size();
    vector<int> minCost = A;
    long long res = accumulate(A.begin(), A.end(), 0LL);
    long long total = res;

    for (int rot = 1; rot < N; ++rot) {
        for (int i = 0; i < N; ++i)
            minCost[i] = min(minCost[i], A[(i + rot) % N]);

        long long sum = accumulate(minCost.begin(), minCost.end(), 0LL) + 1LL * rot * B;
        res = min(res, sum);
    }
    return res;
}

int main() {
    int n; cin >>  n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    int B; cin >> B;
    cout << minimumCost(A, B) << endl;
    return 0;
}
