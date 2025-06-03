#include<iostream>
#include<climits>
#define infinity (INT_MAX/2)
using namespace std;

int path[1001][1001];
int cow[1001];
int n,m,x;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    cin>>n>>m>>x;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=n;++j){
            path[i][j]= infinity;
        }
        path[i][i]=0;
    }
    for (int i=1;i<=m;++i) {
        int u,v,w;
        cin>>u>>v;
        cin>>w;
        path[u][v]=w;
    }

    for (int mid=1;mid<=n;++mid) {
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=n;++j) {
                if (path[i][mid]+path[mid][j]<path[i][j]) {
                    path[i][j]=path[i][mid]+path[mid][j];
                }
            }
        }
    }

    int max=0;
    int distance[1001];
    for (int i=1;i<=n;++i) {
        distance[i] = path[x][i]+path[i][x];
        if (distance[i]>max) {
            max=distance[i];
        }
    }
    cout<<max;
    return 0;
}