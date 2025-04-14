#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
int N;
float t,sum=0;
vector<float> battery;

int main(){
	float max;
	cin>>N;
	for(int i=0;i<N;++i){
	cin>>t;
	sum+=t;
	battery.push_back(t);
	}
	sort(battery.begin(),battery.end());
	max=battery.at(N-1);
	if(max>=sum-max){
		cout<<(sum-max)/;
	}
	else{
		cout<<sum/2;
	}
	return 0;
}

