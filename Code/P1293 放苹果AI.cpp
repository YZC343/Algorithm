#include <iostream>
using namespace std;

int countWays(int m, int n) {
    if (m == 0) {
        return 1;
    }
    if (n == 0) {
        return 0;
    }
    if (m < 0) {
        return 0;
    }
    return countWays(m, n - 1) + countWays(m - n, n);
}

int main() {
    int m, n;
    while (cin >> m >> n) {
        cout << countWays(m, n) << endl;
    }
    return 0;
}