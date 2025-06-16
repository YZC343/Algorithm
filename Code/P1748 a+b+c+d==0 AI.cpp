#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> A(n), B(n), C(n), D(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i] >> B[i] >> C[i] >> D[i];
        }

        unordered_map<int, int> sumAB;
        for (int a : A) {
            for (int b : B) {
                sumAB[a + b]++;
            }
        }

        int count = 0;
        for (int c : C) {
            for (int d : D) {
                int target = -(c + d);
                if (sumAB.find(target) != sumAB.end()) {
                    count += sumAB[target];
                }
            }
        }

        cout << count << '\n';
    }

    return 0;
}