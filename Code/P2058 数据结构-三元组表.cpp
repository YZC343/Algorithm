#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
unsigned int N,r,c,v;
struct node{
	int r;
	int c;
	int v;
}Node;
vector<node>T;
bool comp(struct node a,struct node b){
	return a.v<b.v;
}
int main(){
	cin>>N;
	ios::sync_with_stdio(false); // 关闭C++标准流与C标准流的同步
	cin.tie(0); // 解除cin与cout的绑定
	cout.tie(0);
	for(int i=0;i<N;++i){
		cin>>r>>c>>v;
		Node.r=r;
		Node.c=c;
		Node.v=v;
		T.push_back(Node);
	}
	sort(T.begin(),T.end(),comp);
/*	for(int i=0;i<=N-2;++i){
		for(int j=0;j<=N-2-i;++j){
			if(T[j].v>T[j+1].v){
				swap(T[j],T[j+1]);
			}
		}
	}
*/
	for(int i=0;i<N;++i){
		cout<<T[i].r<<" "<<T[i].c<<" "<<T[i].v<<"\n";
	}
	return 0;
}
