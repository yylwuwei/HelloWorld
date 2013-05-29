// AddAlgo.cpp : Defines the entry point for the console application.
//

//
//使用C++风格和STL重写此程序
//

#include "stdafx.h"
// #include <iostream>
// #include <string>
// 
// int _tmain(int argc, _TCHAR* argv[])
// {
// 	std::string str1 = "123";
// 	std::string str2 = "456";
// 	std::string result;
// 	result = str1 + str2;
// 	std::cout << result << std::endl;
// 	return 0;
// }


#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN=1000010;
char str[MAXN],s[MAXN*2];
int n,p[MAXN*2],ans,cases=1;

void rebuild()
{
	s[0]='$',s[1]='#';
	n=strlen(str);
	for(int i=0;i<n;++i)
		s[2*i+2]=str[i],s[2*i+3]='#';
	s[n=n*2+2]=0;
	printf("%s\n", s);
}

void solve()
{
	int mx=0,ans=1;
	for(int i=0;i<n;++i)
	{
		if(mx>i)
			p[i]=min(p[i-2],p[i-1]);//p[i] is '#'
		else 
			p[i]=1; //p[i] is pre char
		for(;s[i-p[i]]==s[i+p[i]];p[i]++);
		if(p[i]+i>mx)
			mx=p[i]+i;
		ans=max(ans,p[i]);
	}
	printf("Case %d: %d\n",cases++,ans-1);
}

int main()
{
	while(scanf("%s",str),str[0]-'E')
	{
		rebuild();
		solve();
	}
	return 0;
}
