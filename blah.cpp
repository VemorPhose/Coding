#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pub push_back
#define pii pair<int, int>
#define mp make_pair

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> Pos(M);
    for (int i = 0; i < M; ++i) cin >> Pos[i];

    set<pair<pair<int, int>, int>> intervals;
    vector<int> A(N + 2, 0); // 1-indexed bit array
    set<int> robot_pos; // to track where robots are

    int min_pos = INT_MAX, max_pos = INT_MIN;

    for (int t = 0; t < M; ++t) {
        int x = Pos[t];

        if (robot_pos.count(x)) continue;

        robot_pos.insert(x);

        // update min and max robot position
        bool new_interval = false;
        if (x < min_pos || x > max_pos) {
            min_pos = min(min_pos, x);
            max_pos = max(max_pos, x);
            new_interval = true;
        }

        // check if x splits an existing interval
        auto it = intervals.lower_bound({{x + 1, 0}, 0});
        if (it != intervals.begin()) {
            --it;
            int l = it->ff.ff;
            int r = it->ff.ss;
            int time_added = it->ss;
            if (l <= x && x <= r) {
                // remove and split into two
                intervals.erase(it);
                if (l <= x - 1)
                    intervals.insert({{l, x}, time_added});
                if (x + 1 <= r)
                    intervals.insert({{x, r}, time_added});
                A[x] ^= 1;
                continue;
            }
        }

        if (new_interval && robot_pos.size() >= 2) {
            auto it1 = robot_pos.begin();
            auto it2 = prev(robot_pos.end());
            int L = *it1;
            int R = *it2;
            intervals.insert({{L, R}, t});
        }
        cout << "Intervals: " << endl;
        for (const auto& interval : intervals) {
            cout << "[" << interval.ff.ff << ", " << interval.ff.ss << "] " << interval.ss << endl;
        }
    }

    // final count of 1s
    int total = 0;
    for (const auto& interval : intervals) {
        int l = interval.ff.ff;
        int r = interval.ff.ss;
        int time_added = interval.ss;
        if ((M - time_added) % 2 == 1)
            total += r - l + 1;
    }

    for (int i = 1; i <= N; ++i)
        total += A[i];

    cout << total << "\n";
    return 0;
}
