#include <bits/stdc++.h>
using namespace std;
 
int cnt;
int col_total[7],row_total[7];
int n,l;
 
void dfs(int x,int y)
{
    //如果此时填充完了，判断填充完的此种情况是否满足要求
	if(x==n+1&&y==1)
	{
		for(int i=1;i<=n;i++) 
		{
			if(row_total[i]!=l||col_total[i]!=l)
			{
				return;
			}
		}
		cnt++;
		return;
	}
    
   // 还没填充完，就接着填充。根据题目要求可知，只能填充0-9；
	for(int i=0;i<=9;i++)
	{
		if(col_total[x]+i<=l&&row_total[y]<=l)
		{
			col_total[x]+=i;
			row_total[y]+=i;
			//剪枝（填完一行,但是这一行和不等于l）
			if(y==n&&col_total[x]!=l)
			{
				col_total[x]-=i;
				row_total[y]-=i;
				continue;	
			}
            //剪枝（填完一列,但是这一列和不等于l）
			if(x==n&&row_total[y]!=l)
			{
				col_total[x]-=i;
				row_total[y]-=i;
				continue;
			}
			//根据现在的位置x,y判断下一个位置
			if(y<n) dfs(x,y+1);
			else dfs(x+1,1);
            //回溯（还原现场）
			col_total[x]-=i;
			row_total[y]-=i;	
		} 
	}
}
int main()
{
	cin>>l>>n;
	dfs(1,1);
	cout<<cnt<<endl;
	return 0;
}
