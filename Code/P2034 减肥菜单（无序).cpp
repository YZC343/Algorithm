#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<long> a;
vector<long> b;
//vector<int> b;
long m,n,temp,maxa;
int main(){
	cin>>n;
	cin>>m;
	for(int i=0;i<n;++i){
		cin>>temp;
		a.push_back(temp);
	}
	sort(a.begin(),a.end());
	
	for(int i=0;i<m;++i){
		cin>>temp;
		b.push_back(temp);
	}
	
	for(int i=0;i<m;++i){
		maxa=upper_bound(a.begin(),a.end(),b[i])-a.begin();
		cout<<maxa<<"\n";
	}
	
	
	return 0;
}
