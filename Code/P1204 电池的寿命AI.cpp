#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> batteries(N);
    for (int i = 0; i < N; ++i) {
        cin >> batteries[i];
    }

    int sum = 0;
    int max_val = 0;
    for (int num : batteries) {
        sum += num;
        max_val = max(max_val, num);
    }

    double result;
    if (max_val > sum - max_val) {
        result = sum - max_val;
    } else {
        result = sum / 2.0;
    }

    // 判断是否为整数或.5的小数
    if (result == (int)result) {
        cout << fixed << setprecision(1) << result << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}