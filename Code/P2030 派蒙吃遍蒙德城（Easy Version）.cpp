#include<iostream>
using namespace std;
int path[101][101];
int food[101];
int n,m;
int t=0;
int main() {
    for (int i=0;i<=101;++i) {
        for (int j=0;j<=101;++j) {
            path[i][j]=10000;
        }
    }
    cin>>n>>m;
    for (int i=2;i<=n;++i) {
        cin>>food[i];
    }
    for (int i=1;i<=m;++i) {
        int u,v;
        cin>>u>>v;
        path[u][v]=1;
        path[v][u]=1;
    }
    for (int k=1;k<=n;++k) {
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                if (path[i][k]+path[k][j]<path[i][j]) {
                    path[i][j]=path[i][k]+path[k][j];
                }
            }
        }
    }
//    cout<<"path_down"<<endl;
    t+=path[1][2];
    for (int i=2;i<=n-1;++i) {
        t+=food[i];
        if (food[i]+path[i][i+1]<path[i][1]+path[1][i+1]) {
            t+=food[i]+path[i][i+1];
        }
        else {
            t+=path[i][1]+path[1][i+1];
        }
//        cout<<i<<" "<<t<<endl;
    }
    t+=food[n];
    t+=path[n][1];
    cout<<t;
    return 0;
}