#include<iostream>
#include <algorithm>
using namespace std;
/*
int a[6]={1,2,3,4,5,6};
	int* b=lower_bound(a , a+6 , 4);
	cout<<*b;
*/
int main(){
	int N;
	int t[1000000][3];
	int r[1000000][3];
	int k[1000000];
	cin>>N;
	for(i=0;i<N;i++){
		cin>>r[i][0]>>r[i][1]>>r[i][2]; 
		k[i]=r[i][2]; 
	}
	sort(k;k+N);
	for(i=0;i<N;i++){
		int* b=lower_bound(k,k+N,k[i]);
	}
	
} 
