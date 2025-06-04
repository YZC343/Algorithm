#include<iostream>
#include<list>
using namespace std;
list<int> lists[100001];
int access[100001];
int main() {
    int n,m;
    cin>>n>>m;
    for (int i=0;i<=n;++i) {
        int a,b;
        cin>>a>>b;
        lists[a].push_back(b);
        lists[b].push_back(a);
    }
    access[1]=1;
    for (int v : lists[1]) {
        if (access[v]==0) {
            access[v]=1;
        }
    }
}