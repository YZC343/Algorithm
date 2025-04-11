//0:空地 1:障碍物
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
    if(x==fx && y==fy)//输出路径
    /*
    {
        ans++;
        printf("%d号路径：(%d,%d)",ans,sx,sy);
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
        int nx=x+dx[i],ny=y+dy[i];//偏移量
        if(nx<1 || nx>r || ny<1 || ny>c) continue;//是否越界
        if(vis[nx][ny]==0 && g[nx][ny]=='0')//回溯
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
    vis[sx][sy]=1;//起点标记
    px.push_back(sx),py.push_back(sy);//vector存起点
    dfs(sx,sy);

    if(ans==0)
    {
        cout << "没有路径"<<endl;
    }
    return 0;
}
