#include <iostream>
#include <vector>
using namespace std;

const int MAX_NUM = 1e7;

vector<bool> is_bad(MAX_NUM + 1, false);
vector<int> prefix(MAX_NUM + 1, 0);

void preprocess() {
    for (int num = 1; num <= MAX_NUM; ++num) {
        int n = num;
        bool bad = false;
        while (n > 0) {
            int digit = n % 10;
            if (digit == 4) {
                bad = true;
                break;
            }
            n /= 10;
        }
        if (!bad) {
            n = num;
            while (n >= 62) {
                if (n % 100 == 62) {
                    bad = true;
                    break;
                }
                n /= 10;
            }
        }
        is_bad[num] = bad;
        prefix[num] = prefix[num - 1] + (bad ? 0 : 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    preprocess();

    int L, R;
    while (cin >> L >> R) {
        if (L == 0 && R == 0) {
            break;
        }
        cout << prefix[R] - prefix[L - 1] << '\n';
    }

    return 0;
}