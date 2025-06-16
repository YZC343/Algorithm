#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    vector<int> cards(5, 0); // cards[1] to cards[4]
    for (int i = 0; i < M; ++i) {
        int b;
        cin >> b;
        cards[b]++;
    }

    // dp[i][j][k][l] represents max score using i 1-cards, j 2-cards, k 3-cards, l 4-cards
    vector<vector<vector<vector<int>>>> dp(
        cards[1] + 1, vector<vector<vector<int>>>(
            cards[2] + 1, vector<vector<int>>(
                cards[3] + 1, vector<int>(
                    cards[4] + 1, 0))));

    dp[0][0][0][0] = a[0]; // starting at position 1 (0-based: 0)

    for (int i = 0; i <= cards[1]; ++i) {
        for (int j = 0; j <= cards[2]; ++j) {
            for (int k = 0; k <= cards[3]; ++k) {
                for (int l = 0; l <= cards[4]; ++l) {
                    int current_pos = 1 + i * 1 + j * 2 + k * 3 + l * 4;
                    if (current_pos > N) continue; // ensure we don't exceed the board
                    if (i < cards[1]) {
                        int next_pos = current_pos + 1;
                        if (next_pos <= N) {
                            dp[i + 1][j][k][l] = max(dp[i + 1][j][k][l], dp[i][j][k][l] + a[next_pos - 1]);
                        }
                    }
                    if (j < cards[2]) {
                        int next_pos = current_pos + 2;
                        if (next_pos <= N) {
                            dp[i][j + 1][k][l] = max(dp[i][j + 1][k][l], dp[i][j][k][l] + a[next_pos - 1]);
                        }
                    }
                    if (k < cards[3]) {
                        int next_pos = current_pos + 3;
                        if (next_pos <= N) {
                            dp[i][j][k + 1][l] = max(dp[i][j][k + 1][l], dp[i][j][k][l] + a[next_pos - 1]);
                        }
                    }
                    if (l < cards[4]) {
                        int next_pos = current_pos + 4;
                        if (next_pos <= N) {
                            dp[i][j][k][l + 1] = max(dp[i][j][k][l + 1], dp[i][j][k][l] + a[next_pos - 1]);
                        }
                    }
                }
            }
        }
    }

    cout << dp[cards[1]][cards[2]][cards[3]][cards[4]] << endl;

    return 0;
}