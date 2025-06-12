#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T, M;
    cin >> T >> M;
    vector<int> time(M + 1), value(M + 1);
    for (int i = 1; i <= M; ++i) {
        cin >> time[i] >> value[i];
    }

    vector<vector<int>> dp(M + 1, vector<int>(T + 1, 0));
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= T; ++j) {
            if (j >= time[i]) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-time[i]] + value[i]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    cout << dp[M][T] << endl;
    return 0;
}