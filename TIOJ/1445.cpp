#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
#define F first
#define S second

struct edge{
	int a, b;
	ll w;
};
vector<edge> E;
int dsu[1001];
int find(int o){
	return o == dsu[o] ? o : dsu[o] = find(dsu[o]);
}
void Union(int a, int b){
	dsu[find(a)] = find(b);
}

vector<pair<int, ll>> g[1001];
int L;
int dep[1001]{};
int ac[1001][11]{};
ll wa[1001][11]{};
void dfs(int u, int p, ll w, int d){
	dep[u] = d;
	ac[u][0] = p;
	wa[u][0] = w;
	for(int i=0 ; i<L ; ++i){
		ac[u][i+1] = ac[ac[u][i]][i];
		wa[u][i+1] = max(wa[u][i], wa[ac[u][i]][i]);
	}
	for(auto [v, ww]: g[u]){
		if(v != p){
			dfs(v, u, ww, d + 1);
		}
	}
}
ll jump(int &x, int y){
	ll res = 0;
	for(int i=L ; ~i ; --i){
		if(y & (1<<i)){
			res = max(res, wa[x][i]);
			x = ac[x][i];
		}
	}
	return res;
}
ll lca(int a, int b){
	if(dep[a] > dep[b]) swap(a, b);
	ll res = jump(b, dep[b] - dep[a]);
	if(a == b) return res;
	for(int i=L ; ~i ; --i){
		if(ac[a][i] != ac[b][i]){
			res = max({res, wa[a][i], wa[b][i]});
			a = ac[a][i];
			b = ac[b][i];
		}
	}
	return max({res, wa[a][0], wa[b][0]});
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	L = __lg(n);
	while(m--){
		int a, b;
		ll w;
		cin >> a >> b >> w;
		E.eb(edge{a, b, w});
	}
	sort(iter(E), [&](edge &i, edge &j){
		return i.w < j.w;
	});
	for(int i=1 ; i<=n ; ++i){
		dsu[i] = i;
	}
	ll mst = 0;
	int ecnt = 0;
	vector<edge> nd; 
	for(auto [a, b, w]: E){
		if(find(a) != find(b)){
			mst += w;
			Union(a, b);
			g[a].eb(b, w);
			g[b].eb(a, w);
			ecnt++;
		}
		else{
			nd.eb(edge{a, b, w});
		}
	}
	if(ecnt != n - 1){
		cout << "-1 -1\n";
	}
	else if(nd.empty()){
		cout << mst << " -1\n";
	}
	else{
		dfs(1, 1, 0, 0);
		ll scnt = 1LL<<58;
		for(auto [a, b, w]: nd){
			ll val = lca(a, b);
			scnt = min(scnt, w - val);
		}
		cout << mst << ' ' << mst + scnt << '\n';
	}
	return 0;
}
