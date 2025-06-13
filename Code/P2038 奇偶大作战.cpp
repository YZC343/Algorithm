#include<iostream>
using namespace std;
short s[10000000];
short sing[10000000];
short doub[10000000];
short mix[10000000];
short max_sing=0;
short max_doub=0;
short max_mix=0;
short n;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n;
    for (int i=0;i<n;++i) {
        int t;
        cin>>t;
        s[i]=t%2;
    }
    if (s[0]==0) {
        doub[0]=1;
        max_doub=1;
        mix[0]=1;
        max_mix=1;
    }
    else {
        sing[0]=1;
        max_sing=1;
        mix[0]=1;
        max_mix=1;
    }
    for (int i=1;i<n;++i) {
        if (s[i]==0) {
            sing[i]=0;
            if (s[i-1]==0) {
                doub[i]=doub[i-1]+1;
                mix[i]=1;
                if (doub[i]>max_doub) {
                    max_doub=doub[i];
                }
            }
            else {
                mix[i]=mix[i-1]+1;
                doub[i]=1;
                if (max_mix<mix[i]) {
                    max_mix=mix[i];
                }
            }
        }
        else {
            doub[i]=0;
            if (s[i-1]==0) {
                mix[i]=mix[i-1]+1;
                sing[i]=1;
                if (max_mix<mix[i]) {
                    max_mix=mix[i];
                }
            }
            else {
                sing[i]=sing[i-1]+1;
                mix[i]=1;
                if (max_sing<sing[i]) {
                    max_sing=sing[i];
                }
            }
        }
    }
    short max2=max_sing<max_doub?max_doub:max_sing;
    cout<<max_mix-max2;
    return 0;
}
//23
//0 0 0 1 1 1 0 0 0 0 1 1 1 1 0 0 0 0 1 0 0 0 0
//-1


//23
//0 0 0 1 1 1 0 0 0 0 1 1 1 1 0 1 0 1 0 1 0 0 0
//4