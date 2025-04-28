#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int F(int A0,int A1,int i){
	if(i>=2){
		return F(A0,A1,i/2)+F(A0,A1,i/4);
	}
	else if(i==1){
		return A1;
	}
	else{
		return A0;
	}
}

int T(int A0,int A1,int Z,int N){
	int bot=0,top=Z;
	while(bot<=top){
		int mid=(bot+top)/2;
		if(F(A0,A1,mid)==N){
			while(F(A0,A1,mid-1)==N){
				--mid;
			}
			return mid;
		}
		else if(F(A0,A1,mid)<N){
			bot=mid+1;
		}
		else{
			top=mid-1;
		}
	}
	return -1;
}
int main(){
	int t=1,sum=0;
	for(int i=2;i<200;++i){
		cout<<F(11,17,i)<<" ";
		sum++;
		if(sum==pow(2,t)){
			cout<<"\n";
			++t;
			sum=0;
		}
	}
	
	return 0;
}
