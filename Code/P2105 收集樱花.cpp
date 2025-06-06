#include<iostream>
#include<vector>
using namespace std;
int trees[200001];
int sum_flowers[200001];
int max_trees[200001];
int max_flowers;
int n,V;
int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);



    max_flowers=0;
    cin>>n>>V;
    for (int i=1;i<=n;++i) {
        cin>>trees[i];
        sum_flowers[i]=sum_flowers[i-1]+trees[i];
    }
    /*
    for (int i=1;i<=n;++i) {
        cout<<sum_flowers[i]<<" ";
    }
    */

    for (int i=1;i<=n;++i) {
        max_trees[i]=max_trees[i-1]+1;
        while (sum_flowers[i]-sum_flowers[i-1-max_trees[i]]>V) {
            --max_trees[i];
        }
        if (sum_flowers[i]-sum_flowers[i-1-max_trees[i]]>max_flowers) {
            max_flowers=sum_flowers[i]-sum_flowers[i-1-max_trees[i]];
        }
    }
    cout<<max_flowers;

    return 0;
}