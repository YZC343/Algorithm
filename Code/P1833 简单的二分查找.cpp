#include<iostream>
using namespace std;
int main(){
	long x,y,z;
	long s;
	cin>>x>>y;
	cin>>s;
	
	while(x<=y){
		z=(x+y)/2;
		if(z==s){
			cout<<"G";
			return 0;
		}
		else if(z<s){
			x=z+1;
			cout<<"R";
		}
		else{
			y=z-1;
			cout<<"L";
		}
	}
	return 0;
}
