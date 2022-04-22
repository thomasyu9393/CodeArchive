#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define eb emplace_back
const int N = 1001;

vector<int> g[N];
string s[N];
int dp[N][26];
void dfs(int u, int p){
	for(int i=0 ; i<26 ; ++i){
		dp[u][i] = (s[u][p] == '@' || s[u][p] == i + 'A' ? 0 : 1e9);
	}
	for(int v: g[u]){
		dfs(v, p);
		for(int i=0 ; i<26 ; ++i){
			if(s[u][p] != '@' && s[u][p] != i + 'A') continue;
			int mn = 1e9;
			for(int j=0 ; j<26 ; ++j){
				mn = min(mn, dp[v][j] + (i != j));
			}
			dp[u][i] += mn;
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, m, rt;
	cin >> n >> m;
	for(int i=0 ; i<n ; ++i){
		int v, u;
		string ss;
		cin >> v >> u >> ss;
		s[v] = ss;
		if(v == u){
			rt = v;
		}
		else{
			g[u].eb(v);
		}
	}
	int ans = 0;
	for(int i=0 ; i<m ; ++i){
		dfs(rt, i);
		ans += *min_element(dp[rt], dp[rt] + 26);
	}
	cout << ans << '\n';
}
