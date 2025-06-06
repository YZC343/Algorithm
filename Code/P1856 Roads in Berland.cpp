#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int n,k;
int w[301][301];
int r[301][3];
void F(int u,int v,int w1) {
    if (w[u][v]>w1) {
        w[u][v]=w1;
        w[v][u]=w1;
    }
    queue<vector<int>> q;
    q.push({u,v});
    q.push({v,u});
    while (q.empty()==false) {
        int u2=q.front()[0];
        int v2=q.front()[1];
        q.pop();
        for (int i=1;i<=n;++i) {
            if (w[u2][v2]+w[v2][i]<w[u2][i]) {
                w[u2][i]=w[u2][v2]+w[v2][i];
                q.push({u2,i});
            }
            if (w[i][u2]+w[u2][v2]<w[i][v2]) {
                w[i][v2]=w[i][u2]+w[u2][v2];
                q.push({i,v2});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for (int i=1;i<=300;++i) {
        for (int j=1;j<=300;++j) {
            w[i][j]=10000;
        }
    }
    cin>>n;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j) {
            cin>>w[i][j];}
    }
    cin>>k;
    for (int i=1;i<=k;++i) {
        cin>>r[i][0]>>r[i][1]>>r[i][2];
    }

    for (int k=1;k<=n;++k) {
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                if (w[i][k]+w[k][j]<w[i][j]) {
                    w[i][j]=w[i][k]+w[k][j];
                }
            }
        }
    }

    for (int i=1;i<=k;++i) {
        F(r[i][0],r[i][1],r[i][2]);
        int dis_sum=0;
        for (int i=1;i<=n;++i) {
            for (int j=1;j<i;++j) {
                dis_sum+=w[i][j];
            }
        }
        cout<<dis_sum<<" ";
    }
    return 0;
}