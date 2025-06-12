#include<iostream>
#include<vector>
#include<functional>
#include <queue>
#include<algorithm>
using namespace std;

int main() {
    priority_queue<int,vector<int>,greater<int>> minHeap;
    int m,n,p,t=0;
    int stu[10001];
    cin>>n>>m;
    p=1;
    int volum = 0;
    for (int i=1;i<=n;++i) {
        cin>>stu[i];
    }
    while (volum<m) {
        minHeap.push(stu[p++]);
        volum++;
    }
    while (p<=n) {
        int min = minHeap.top();
        minHeap.pop();
        volum--;
        t+= min;
        while (minHeap.top()==min) {
            minHeap.pop();
            volum--;
        }
        int temp[100];
        for (int i=0;i<volum;++i) {
            temp[i]=minHeap.top()-min;
            minHeap.pop();
//            cout<<temp[i]<<" ";
        }
//        cout<<endl;
        for (int i=0;i<volum;++i) {
            minHeap.push(temp[i]);
        }
        while (volum<m&&p<=n) {
            minHeap.push(stu[p++]);
            volum++;
        }

    }
    while (volum>1) {
        minHeap.pop();
        volum--;
    }
    t+=minHeap.top();
    cout<<t;
    return 0;
}
