#include<iostream>
#include<list>
#include<queue>
using namespace std;
list<int> lists[100001];
int access[100001];
int main() {
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;++i) {
        int a,b;
        cin>>a>>b;
        lists[a].push_back(b);
        lists[b].push_back(a);
    }
    access[1]=1;
    queue<int> q;
    for (int v : lists[1]) {
        if (access[v]==0) {
            access[v]=1;
            q.push(v);
        }
    }
    while (q.empty()==false) {
        int i= q.front();
        for (int v : lists[i]) {
            if (access[v]==0) {
                access[v]=1;
                q.push(v);
            }
        }
        q.pop();
    }

    int count =0;
    for (int i=1;i<=n;++i) {
        if (access[i]==1) {
            count++;
        }
    }
    cout<<(n-count);
    return 0;
}