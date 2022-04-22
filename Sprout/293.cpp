#include <iostream>
#include <vector>
using namespace std;
#define eb emplace_back
inline void chmax(int &a, int b){a = (a < b ? b : a);}
inline void chmin(int &a, int b){a = (a > b ? b : a);}

int n;
vector<int> g[100005];
int sz[100005];
int mxsz, ans;
void dfs(int u, int p){
	sz[u] = 1;
	int mxsub = 0;
	for(int v: g[u]){
		if(v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
		chmax(mxsub, sz[v]);
	}
	chmax(mxsub, n - sz[u]);
	if(mxsub < mxsz){
		ans = u;
		mxsz = mxsub;
	}
	else if(mxsub == mxsz){
		chmin(ans, u);
	}
}
int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		for(int i=0 ; i<n ; ++i){
			g[i].clear();
		}
		for(int i=1 ; i<n ; ++i){
			int x, y;
			cin >> x >> y;
			g[x].eb(y);
			g[y].eb(x);
		}
		mxsz = n;
		dfs(0, 0);
		cout << ans << '\n';
	}
}
