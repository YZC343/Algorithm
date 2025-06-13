#include<iostream>
using namespace std;
int path[101][101];
int x,y,m,n;
int t_LX,t_ZS;
int main() {
    for (int i=0;i<101;++i) {
        for (int j=0;j<101;++j) {
            path[i][j]=10000;
        }
    }
    cin>>n>>m>>x>>y;
    for (int k=1;k<=m;++k) {
        int i,j,d;
        cin>>i>>j>>d;
        path[i][j]=d;
        path[j][i]=d;
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
    t_LX=path[x][n];
    t_ZS=path[y][n];
    if (t_LX<=t_ZS) {
        cout<<"YES "<<t_LX;
    }
    else {
        cout<<"NO "<<t_ZS;
    }
    return 0;
}