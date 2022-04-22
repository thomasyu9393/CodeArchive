#include <bits/stdc++.h>
using namespace std;
#define jass_FHVirus_8e7_Orz ios_base::sync_with_stdio(false), cin.tie(0);

int OAO[22][100001];
int dp[22][100001][2]{};
int sum[100001];
int main(){
	jass_FHVirus_8e7_Orz
	int n, m;
	cin >> n >> m;
	for(int i=1 ; i<=m ; ++i)
		for(int j=1 ; j<=n ; ++j)
			cin >> OAO[i][j], sum[j] += OAO[i][j];
	for(int i=1 ; i<=n ; ++i){
		for(int j=1 ; j<=m ; ++j){
			dp[j][i][0] = max({dp[j-1][i-1][0], dp[j][i-1][0], dp[j+1][i-1][0]}) + OAO[j][i];
			dp[j][i][1] = max(max({dp[j-1][i-1][0], dp[j][i-1][0], dp[j+1][i-1][0]}) + sum[i],
							  max({dp[j-1][i-1][1], dp[j][i-1][1], dp[j+1][i-1][1]}) + OAO[j][i]);
		}
	}
	int ans = 0;
	for(int i=1 ; i<=m ; ++i){
		ans = max(ans, dp[i][n][1]);
	}
	cout << ans;
}
