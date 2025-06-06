#include<iostream>
#include<queue>
using namespace std;
int K,M,N;
int mazes[10][52][52];
int maze[52][52];
int access[52][52];
char C;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
queue<vector<int>> q;
int main() {
    cin>>K>>M>>N;
    for (int m=0;m<K;++m) {
        for (int i=1;i<=M;++i) {
            for (int j=1;j<=N;++j) {
                cin>>C;
                if (C=='G') {
                    mazes[m][i][j]=0;
                }
                else if (C=='W') {
                    mazes[m][i][j]=3;
                }
                else if (C=='X') {
                    mazes[m][i][j]=1;
                }
            }
        }
    }
    for (int m=0;m<K;++m) {
        for (int i=0;i<52;++i) {
            for (int j=0;j<52;++j) {
                maze[i][j]=3;
                access[i][j]=0;
            }
        }


        for (int i=1;i<=M;++i) {
            for (int j=1;j<=N;++j) {
                maze[i][j]=mazes[m][i][j];
            }
        }
        q.push({1,1});
        access[1][1]=3;
        while (q.empty()==false) {
            int x=q.front()[0];
            int y=q.front()[1];
            q.pop();
            for (int i=0;i<4;++i) {
                if (access[x][y]-maze[x+dx[i]][y+dy[i]]>access[x+dx[i]][y+dy[i]]) {
                    access[x+dx[i]][y+dy[i]]=access[x][y]-maze[x+dx[i]][y+dy[i]];
                    q.push({x+dx[i],y+dy[i]});
                }
            }
        }
        if (access[M][N]>0) {
            cout<<"YES"<<endl;

        }
        else {
            cout<<"NO"<<endl;
        }
        /*
        for (int i=1;i<=M;++i) {
            for (int j=1;j<=N;++j) {
                cout<<maze[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for (int i=1;i<=M;++i) {
            for (int j=1;j<=N;++j) {
                cout<<access[i][j]<<" ";
            }
            cout<<endl;
        }
    */
    }

    return 0;

}
