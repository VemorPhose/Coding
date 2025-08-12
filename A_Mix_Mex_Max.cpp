#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        set<int> s;
        for (int i = 0; i < n; i++) {
            s.insert(a[i]);
        }
        if (s.size() == 2 && s.count(-1) && !s.count(0)) {
            cout << "YES" << endl;
        } else if (s.size() == 1 && !s.count(0)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}