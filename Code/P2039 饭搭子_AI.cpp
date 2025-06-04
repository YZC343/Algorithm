#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    vector<int> f(n);
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
    }
    sort(f.begin(), f.end());
    int left = 0, right = n - 1;
    int tables = 0;
    while (left <= right) {
        if (f[left] + f[right] <= W) {
            left++;
        }
        right--;
        tables++;
    }
    cout << tables << endl;
    return 0;
}