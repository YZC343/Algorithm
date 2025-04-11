#include<iostream>
using namespace std;
void F(int a,int b,int m,int n,int &c){
	if(a==m&&b==n){
		c++;
	}
	else if(a<m&&b<n){
		F(a+2,b+1,m,n,c);
		F(a+1,b+2,m,n,c);
	}
}

int main(){
	int m,n;
	cin>>n>>m;
	int c=0;
	F(1,1,m,n,c);
	cout<<c;
	return 0;
}
