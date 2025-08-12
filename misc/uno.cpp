#include <iostream>
#include <set>
#include <tuple>
#include <cstdlib>
using namespace std;

int gcd_two(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int maxLines(int N, int x[], int y[]) {
    set<tuple<int, int, int>> lineSet;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int a = y[i] - y[j];
            int b = x[j] - x[i];
            int c = x[i] * y[j] - x[j] * y[i];

            int g1 = gcd_two(a, b);
            if (g1 == 0) {
                continue;
            }

            int abs_c = abs(c);
            int g2 = gcd_two(g1, abs_c);
            if (g2 == 0) {
                continue;
            }

            a /= g2;
            b /= g2;
            c /= g2;

            if (a < 0) {
                a = -a;
                b = -b;
                c = -c;
            } else if (a == 0) {
                if (b < 0) {
                    b = -b;
                    c = -c;
                }
            }

            lineSet.insert(make_tuple(a, b, c));
        }
    }

    int totalLines = 0;
    for (auto line : lineSet) {
        int a = get<0>(line);
        int b = get<1>(line);
        int c = get<2>(line);
        int cnt = 0;
        for (int k = 0; k < N; k++) {
            long long val = static_cast<long long>(a) * x[k] + static_cast<long long>(b) * y[k] + c;
            if (val == 0) {
                cnt++;
            }
        }
        if (cnt >= 3) {
            totalLines++;
        }
    }

    return totalLines;
}

int main() {
    int N;
    cin >> N;
    int x[N], y[N];
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
    }
    cout << maxLines(N, x, y);
    return 0;
}
