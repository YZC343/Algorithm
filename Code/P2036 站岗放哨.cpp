#include <iostream>
#include <algorithm>
using namespace std;
void F(int a,int b,int r,int &t){
	if(b==1){
		t+=r*a;
	}
	else{
		F(a-1,b-1,r*a,t);
	}
}

int C(int a){
	int r=1;
	while(a>1){
		r*=a;
		a--;
	}
	return r;
}
int main(){
	int n,m;
	int r1[20],t=0;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>r1[i];
	}
	sort(r1,r1+n);
	F(n,m,1,t);
	cout<<t/C(m);
	return 0; 
} 
