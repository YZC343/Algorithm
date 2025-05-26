#include<iostream>
#include<string>
#include<cstdio>
#include<string>
using namespace std;
void fun(string in , string pre)
{
	if(!pre.empty())
	{
		char root = pre[0];
		int k = in.find(root);
		pre.erase(pre.begin());
		fun(in.substr(0,k),pre.substr(0,k));
		fun(in.substr(k+1),pre.substr(k));
		cout << root;
	 
	}
 
}
 
int main()
 
{
	string in,af;
	cin >> in >> af;
	fun(in,af);
	getchar();
	getchar();
	return 0;

}
