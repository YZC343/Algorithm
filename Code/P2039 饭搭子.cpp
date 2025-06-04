#include<iostream>
#include<algorithm>
using namespace std;
int n,W;
int f[10000000];
int main() {
    int table=0;
    cin>>n>>W;
    int left=0,right=n-1;
    for (int i=0;i<n;++i) {
        cin>>f[i];
    }
    sort(&f[0],&f[n-1]);
    while (left<=right) {
        if (f[left]+f[right]<=W) {
            ++table;
            ++left;
            --right;
        }
        else {
            --right;
            ++table;
        }
    }
    /*
    if (left==right) {
        ++table;
    }
    */
    cout<<table;
    return 0;
}
//26 7
//1 1 2 2 2 2 2 2 4 4 4 4 4 4 5 5 5 6 6 6 6 7 7 8 8 8