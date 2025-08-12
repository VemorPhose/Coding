#include <bits/stdc++.h>
using namespace std;

vector<int> allocate_resources(vector<int>& performance, int inc, int dec) {
    int n = performance.size();
    map<int, int, greater<int>> freq;
    for (auto &x: performance) {
        freq[x]++;
    }
    int ind = 1;
    unordered_map<int, int> rank;
    for (auto &p: freq) {
        rank[p.first] = ind++;
    }
    vector<int> res;
    for (auto &x: performance) {
        res.push_back(inc * (n + 1 - rank[x]) - dec * (freq[x]));
    }
    return res;
}

int main() {
    vector<int> performance = {3, 2, 4, 3, 5, 5};
    int inc = 500, dec = 100;
    
    vector<int> result = allocate_resources(performance, inc, dec);
    
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}