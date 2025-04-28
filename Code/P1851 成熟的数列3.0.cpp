#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
long Ms[30];
long X,Y;
int Z,N,size;
int main(){
	cin>>X;
	cin>>Y;
	cin>>Z;
	cin>>N;
	Ms[0] = X;
	Ms[1] = Y;
	size = log(Z)/log(2)+2;
	for(int i=2;i<size;++i){
		Ms[i]=Ms[i-1]+Ms[i-2];
//		cout<<Ms[i]<<" ";
	}
	for(int i=0;i<N;++i){
		long temp;
		cin>>temp;
		if(temp==Ms[0]){
			cout<<"0\n";
		}
		else if(temp==Ms[1]){
			cout<<"1\n";
		}
		else{
			long *index = lower_bound(Ms,Ms+size,temp);
			if(index!=Ms+size&&Ms[index-Ms]==temp){
				cout<<pow(2,index-Ms-1)<<"\n";
			}
			else{
				cout<<"-1\n";
			}
		}
	}
	return 0;
}
