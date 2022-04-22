#include <bits/stdc++.h>
using namespace std;

int mp[2][10001];
int dp[2][10001]{};
int L[10001], R[10001];
int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	int now = 0, prv = 1;
	for(int i=0 ; i<n ; ++i){
		for(int j=0 ; j<m ; ++j)
			cin >> mp[now][j];
		L[0] = dp[prv][0] + mp[now][0];
		for(int j=1 ; j<m ; ++j)
			L[j] = max(dp[prv][j], L[j-1]) + mp[now][j];
		R[m-1] = dp[prv][m-1] + mp[now][m-1];
		for(int j=m-2 ; j>=0 ; --j)
			R[j] = max(dp[prv][j], R[j+1]) + mp[now][j];
		for(int j=0 ; j<m ; ++j)
			dp[now][j] = max(L[j], R[j]);
		now ^= 1, prv ^= 1;
	}
	cout << *max_element(dp[prv], dp[prv]+m) << '\n';
}
