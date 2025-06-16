#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> cows(n);
    for (int i = 0; i < n; ++i) {
        cin >> cows[i].first >> cows[i].second;
    }
    
    // 按开始时间排序
    sort(cows.begin(), cows.end());
    
    // 最小堆，存储当前使用的蓄栏的结束时间
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for (const auto& cow : cows) {
        if (!pq.empty() && pq.top() < cow.first) {
            // 可以复用这个蓄栏
            pq.pop();
        }
        pq.push(cow.second);
    }
    
    cout << pq.size() << endl;
    
    return 0;
}