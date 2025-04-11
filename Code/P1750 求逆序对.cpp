#include<iostream>
#include<cstdlib>
using namespace std;
int main(){
	long* list=(long*)malloc(500000*sizeof(long));
	int n,num=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>list[i];
	}
	for(int i=1;i<=n-1;i++){
		for(int j=i+1;j<=n;j++){
			if(list[i]>list[j]){
				num++;
			}
		}
	}
	cout<<num;
	return 0;
} 
