#include <iostream>
using namespace std;
int max_dis =0;
int max_T = -1;
void dfs(int M,int S,int dis,int T) {
    if (dis>=S) {
        if (T>max_T) {
            max_T=T;
            max_dis = dis;
        }
    }
    else {
        if (T==0) {
            if (dis>max_dis) {
                max_dis = dis;
            }
        }
        else if (T>0) {
            if (M>=10) {
                dfs(M-10,S,dis+60,T-1);
            }
            else {
                dfs(M+4,S,dis,T-1);
                dfs(M,S,dis+17,T-1);
            }
        }

    }
}
int main() {
    int M,S,T,t;
    int distance = 0;
    cin>>M>>S>>T;
    t=T;
    int M1=M,S1=S,T1=T;
    while (M1>=10&&T1>=1) {
        S1-=60;
        T1--;
        M1-=10;
        if (S1<=0) {
            cout<<"Yes"<<endl;
            cout<<t-T1;
            return 0;
        }
    }
    ///
    while (M>=10 && T>0) {
        T--;
        distance +=60;
        M -= 10;
        if (distance>=S) {
            cout<<"Yes"<<endl;
            cout<<t-T;
            return 0;
        }
    }
    if (T==0) {
        cout<<"No"<<endl;
        cout<<distance;
        return 0;
    }
    ///
    int loop_time=0;
    if (T>7) {
        loop_time = T/7;
        T = T%7;
    }
    distance += loop_time*120;
//    cout<<M<<" "<<distance<<" "<<T<<endl;
    dfs(M,S,distance,T);
    if (max_T>=0&&max_dis>=S) {
        cout<<"Yes"<<endl;
        cout<<t-max_T;
    }
    else {
        cout<<"No"<<endl;
        cout<<max_dis;
    }
    return 0;
}
