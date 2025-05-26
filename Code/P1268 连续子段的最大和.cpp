#include<iostream>
#include<limits.h>
using namespace std;
#define INF INT_MAX

int main(){
    int res=-INF;
    int nums[10001],dp[10001];
    int N;
    cin>>N;
    for(int i=1;i<=N;++i){
    	cin>>nums[i];
    }
    dp[0]=0;
    for(int i=1;i<=N;i++){
        dp[i]=max(dp[i-1]+nums[i],nums[i]);
        res=max(dp[i],res);
    }
    cout<<res;
    return 0;
}

//31 -41 59 26 -53 58 97 -93 -23 84

