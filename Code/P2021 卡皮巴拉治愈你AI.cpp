#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, K, M;
    cin >> N >> K >> M;
    vector<int> pressure(N);
    for (int i = 0; i < N; ++i) {
        cin >> pressure[i];
    }

    // Precompute the sum of pressure for each possible position
    vector<int> sum(N, 0);
    for (int i = 0; i < N; ++i) {
        int left = max(0, i - M);
        int right = min(N - 1, i + M);
        for (int j = left; j <= right; ++j) {
            sum[i] += pressure[j];
        }
    }

    // DP table: dp[k][i] = max sum using k capybaras up to position i
    vector<vector<int>> dp(K + 1, vector<int>(N, 0));
    for (int k = 1; k <= K; ++k) {
        for (int i = 0; i < N; ++i) {
            if (i >= 2 * M + 1) {
                dp[k][i] = max(dp[k][i - 1], dp[k - 1][i - 2 * M - 1] + sum[i]);
            } else {
                dp[k][i] = max((i > 0 ? dp[k][i - 1] : 0), sum[i]);
            }
        }
    }

    cout << dp[K][N - 1] << endl;

    return 0;
}