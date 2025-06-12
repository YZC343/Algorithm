#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << nums[0] << endl;
        return 0;
    }

    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = nums[0];
    for (int i = 2; i <= n; ++i) {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]);
    }

    cout << dp[n] << endl;
    return 0;
}
//转移方程:dp[i] = max(dp[i-1], dp[i-2] + nums[i-1])