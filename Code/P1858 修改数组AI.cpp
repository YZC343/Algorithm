#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    unordered_set<int> seen;
    seen.insert(A[0]);
    for (int i = 1; i < N; ++i) {
        while (seen.find(A[i]) != seen.end()) {
            A[i]++;
        }
        seen.insert(A[i]);
    }

    for (int num : A) {
        cout << num << ' ';
    }
    cout << endl;

    return 0;
}