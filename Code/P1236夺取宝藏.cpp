#include<iostream>
#define max 1001
using namespace std;
int maze[max][max];
int maxTreasure[max][max];
int m,n;
int Max(int a,int b) {
    if (a>=b) {
        return a;
    }
    return b;
}
int main() {
    cin>>m>>n;
    for (int i = 1;i<=m;++i) {
        for (int j=1;j<=n;++j) {
            cin>>maze[i][j];
        }
    }
    for (int i = 1;i<=m;++i) {
        for (int j=1;j<=n;++j) {
            maxTreasure[i][j]=maze[i][j]+Max(maxTreasure[i][j-1],(maxTreasure[i-1][j]));
        }
    }
    cout<<maxTreasure[m][n];
    return 0;
}