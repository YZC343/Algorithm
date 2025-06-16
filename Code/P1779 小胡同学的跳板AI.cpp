#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> jump_boards(N);
    for (int i = 0; i < N; ++i) {
        cin >> jump_boards[i].first >> jump_boards[i].second;
    }

    sort(jump_boards.begin(), jump_boards.end());

    int max_reach = 0;
    int walk_distance = 0;
    for (const auto& jb : jump_boards) {
        int pos = jb.first;
        int x = jb.second;
        if (pos > max_reach) {
            walk_distance += pos - max_reach;
            max_reach = pos + x;
        } else {
            max_reach = max(max_reach, pos + x);
        }
        if (max_reach >= M) {
            break;
        }
    }

    if (max_reach < M) {
        walk_distance += M - max_reach;
    }

    cout << walk_distance << '\n';

    return 0;
}