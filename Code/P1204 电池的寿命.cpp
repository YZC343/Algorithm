#include<iostream>
#include<vector>
#include <algorithm>
#include <iomanip>
using namespace std;
int N;
double t,sum=0;
vector<double> battery;

int main(){
	cout.setf(ios::showpoint);
	cout.precision(2);
	double max;
	cin>>N;
	for(int i=0;i<N;++i){
	cin>>t;
	sum+=t;
	battery.push_back(t);
	}
	sort(battery.begin(),battery.end());
	max=battery.at(N-1);
	if(max>=sum-max){
		cout<<(sum-max);
	}
	else{
		cout<<sum/2;
	}
	return 0;
}

