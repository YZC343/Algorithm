#include <bits/stdc++.h>
using namespace std;
 
int cnt;
int col_total[7],row_total[7];
int n,l;
 
void dfs(int x,int y)
{
    //�����ʱ������ˣ��ж������Ĵ�������Ƿ�����Ҫ��
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
    
   // ��û����꣬�ͽ�����䡣������ĿҪ���֪��ֻ�����0-9��
	for(int i=0;i<=9;i++)
	{
		if(col_total[x]+i<=l&&row_total[y]<=l)
		{
			col_total[x]+=i;
			row_total[y]+=i;
			//��֦������һ��,������һ�кͲ�����l��
			if(y==n&&col_total[x]!=l)
			{
				col_total[x]-=i;
				row_total[y]-=i;
				continue;	
			}
            //��֦������һ��,������һ�кͲ�����l��
			if(x==n&&row_total[y]!=l)
			{
				col_total[x]-=i;
				row_total[y]-=i;
				continue;
			}
			//�������ڵ�λ��x,y�ж���һ��λ��
			if(y<n) dfs(x,y+1);
			else dfs(x+1,1);
            //���ݣ���ԭ�ֳ���
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
