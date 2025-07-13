#include <iostream>
#include <vector>
#include <string>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> grid[i];
    }
    std::string word;
    std::cin >> word;

    int word_len = word.length();
    int count = 0;

    int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            
            for (int d = 0; d < 8; ++d) {
                int current_r = r;
                int current_c = c;
                int k;
                for (k = 0; k < word_len; ++k) {
                    if (current_r < 0 || current_r >= n || current_c < 0 || current_c >= n) {
                        break;
                    }
                    if (grid[current_r][current_c] != word[k]) {
                        break;
                    }
                    current_r += dr[d];
                    current_c += dc[d];
                }
                if (k == word_len) {
                    count++;
                }
            }
        }
    }

    std::cout << count << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}