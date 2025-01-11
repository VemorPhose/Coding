#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int64_t
#define pii             pair<ll, ll>
#define vi              vector<ll>
#define vvi             vector<vector<ll>>
#define mpii            map<ll, ll>
#define umpii           unordered_map<ll, ll>

// shortcuts
#define MOD             1000000007
#define INF             LLONG_MAX
#define endl            "\n"

// pairs
#define ff              first
#define ss              second
#define mp              make_pair

// iterable operations
#define all(x)          (x).begin(), (x).end()

// looping
#define FOR(i, a, b)    for (ll i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

vector<ll> max_small_indices(ll T, vector<tuple<ll, vi, vi>> &test_cases) {
    vi results;

    F0R(tc, T) {
        ll N = get<0>(test_cases[tc]);
        vi A = get<1>(test_cases[tc]);
        vi B = get<2>(test_cases[tc]);

        // Initialize C1 and C2
        ll C1 = max(A[0], B[0]);
        ll C2 = max(A[1], B[1]);
        pii initial_key = (C1 >= C2) ? mp(C1, C2) : mp(C2, C1);

        map<pii, ll> dp;
        dp[initial_key] = 0;

        FOR(i, 2, N) {
            map<pii, ll> next_dp;

            for (auto it = dp.begin(); it != dp.end(); ++it) {
                ll max1 = it->ff.ff;
                ll max2 = it->ff.ss;
                ll cnt = it->ss;

                for (ll Ci : {A[i], B[i]}) {
                    ll new_cnt = (Ci <= max1 + max2) ? cnt + 1 : cnt;

                    // Update max1 and max2
                    ll new_max1 = max1, new_max2 = max2;
                    if (Ci > max1) {
                        new_max2 = max1;
                        new_max1 = Ci;
                    } else if (Ci > max2) {
                        new_max2 = Ci;
                    }

                    if (new_max1 < new_max2) swap(new_max1, new_max2);

                    pii new_key = mp(new_max1, new_max2);
                    if (next_dp.find(new_key) == next_dp.end() || next_dp[new_key] < new_cnt) {
                        next_dp[new_key] = new_cnt;
                    }
                }
            }

            dp = move(next_dp);
        }

        ll max_count = 0;
        for (auto it = dp.begin(); it != dp.end(); ++it) {
            max_count = max(max_count, it->ss);
        }
        results.push_back(max_count);
    }

    return results;
}

int main() {
    fastio();

    ll T;
    cin >> T;

    vector<tuple<ll, vi, vi>> test_cases(T);
    F0R(tc, T) {
        ll N;
        cin >> N;
        vi A(N), B(N);
        F0R(i, N) cin >> A[i];
        F0R(i, N) cin >> B[i];
        test_cases[tc] = make_tuple(N, A, B);
    }

    vi results = max_small_indices(T, test_cases);

    for (ll res : results) {
        cout << res << endl;
    }

    return 0;
}
