//0:�յ� 1:�ϰ���
#include<iostream>
#include<vector>
#include<stdio.h>
#define Size 50
using namespace std;
vector<int> px,py;
int dx[4]={1,0,0,-1};
int dy[4]={0,1,-1,0};
int vis[50][50],ans=0,r,c,sx,sy,fx,fy;
char g[50][50];
void dfs(int x,int y)
{
    if(x==fx && y==fy)//���·��
    /*
    {
        ans++;
        printf("%d��·����(%d,%d)",ans,sx,sy);
        for(int i=1;i<px.size();i++)
        {
            printf("->(%d,%d)",px[i],py[i]);
        }
        cout << endl;
        return ;
    }
    */
    {
    	cout<<px.size();
    }
    
    for(int i=0;i<4;i++)
    {
        int nx=x+dx[i],ny=y+dy[i];//ƫ����
        if(nx<1 || nx>r || ny<1 || ny>c) continue;//�Ƿ�Խ��
        if(vis[nx][ny]==0 && g[nx][ny]=='0')//����
        {
            vis[nx][ny]=1;
            px.push_back(nx),py.push_back(ny);

            dfs(nx,ny);

            vis[nx][ny]=0;
            px.pop_back(),py.pop_back();
        }
    }
}
int main()
{
    cin >> r>> c;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin >> g[i][j];
        }
    }
    cin >> sx>>sy >> fx>> fy;
    vis[sx][sy]=1;//�����
    px.push_back(sx),py.push_back(sy);//vector�����
    dfs(sx,sy);

    if(ans==0)
    {
        cout << "û��·��"<<endl;
    }
    return 0;
}
