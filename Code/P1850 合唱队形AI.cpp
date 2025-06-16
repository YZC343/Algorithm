#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    vector<int> lis(n, 1); // Longest Increasing Subsequence from left to right
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (heights[j] < heights[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    vector<int> lds(n, 1); // Longest Decreasing Subsequence from right to left (LIS from right to left)
    for (int i = n - 2; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            if (heights[j] < heights[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        max_len = max(max_len, lis[i] + lds[i] - 1);
    }

    cout << n - max_len << endl;

    return 0;
}