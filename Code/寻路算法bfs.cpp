#include<bits/stdc++.h>
using namespace std;
struct node 
{ 
	int x,y;
	int step;
} S,T,Node;
int n,m;
int tmp;
const int maxn = 55;
int maze[maxn][maxn];
bool inq[maxn][maxn]={false};
int X[4]={-1,0,0,1};
int Y[4]={0,-1,1,0};

bool test(int x,int y) {
	if(x>n || x<=0 || y>m || y<=0) return false;
	if(maze[x][y]==1) return false;
	if(inq[x][y]==true) return false;
	return true;
}
int BFS() {
	queue<node> q;
	q.push(S);
	while(!q.empty()) {
		node top = q.front();
		q.pop();
		if(top.x == T.x && top.y == T.y) {
			return top.step;
		}
		for(int i=0; i<4; i++) {
			int newX = top.x+X[i];
			int newY = top.y+Y[i];
			if(test(newX,newY)) {
				Node.x = newX;
				Node.y = newY;
				Node.step = top.step +1;
				q.push(Node);
				inq[newX][newY] = true;
			}
		}
	}
	return -1;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			scanf("%d",&tmp);
			if(tmp == 0) {
				maze[i][j] = 0;
			} else {
				maze[i][j] = 1;
			}
		}
	}
	scanf("%d%d",&S.x,&S.y);
	scanf("%d%d",&T.x,&T.y);
	S.step = 0;
	printf("%d\n",BFS());
	return 0;
}

