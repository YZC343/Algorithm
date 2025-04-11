#include<iostream>
using namespace std;

int main(){
	int T,n;
	cin>>T;
	while(T-->=1)
	{
		cin>>n;
		int card[101];
		for(int i=1;i<=n;++i){
			card[i]=i;
		}
		while(n>1){
			card[0]=card[2];
			for(int j=2;j<=n;++j){
				card[j-2]=card[j];
			}
			card[n-1]=card[0];
			--n;
		}
		cout<<card[1];
		cout<<"\n";
	}
	
	return 0;
}
