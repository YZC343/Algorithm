#include<iostream>
using namespace std;
int main(){
	int T[100][100];
	int n;
	int v=0;
	cin>>n;
	for(int i=0;i<n;i++){
		int e=0;
		for(int j=0;j<n;j++){
			cin>>T[i][j];
			if(T[i][j]==1){
				++e;
			} 
		}
		if(e%2!=0){
			++v;
		}
	}
	if(v==0||v==2){
		cout<<"YES";
	}
	else{
		cout<<"NO";
	}
}
