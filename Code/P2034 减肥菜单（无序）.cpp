#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n,m;
int a[100000];
int b[100000];
int main() {
    cin>>n>>m;
    for (int i=0;i<n;++i) {
        cin>>a[i];
    }
    for (int j=0;j<m;++j) {
        cin>>b[j];
    }
    sort(a,a+n);
    for (int j=0;j<m;++j) {
        if (b[j]>=a[n-1]) {
            cout<<n<<endl;
        }
        else {
            cout<<(upper_bound(a,a+n,b[j])-a)<<endl;
        }
    }
    return 0;
}

/*
5 3
2 8 6 10 4
15
1
4
*/