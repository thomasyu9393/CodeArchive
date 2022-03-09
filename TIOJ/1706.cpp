#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define ll long long
#define eb emplace_back

const int maxn = 100005;
const ll INF = 1e18;

struct edge{
	int v;
	ll c, p;
};
vector<edge> g[maxn];

ll dp[maxn];
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
ll go(int s, int t, ll d){
	fill(dp, dp + maxn, INF);
	dp[s] = 0;
	pq.emplace(0, s);
	while(pq.size()){
		auto [w, u] = pq.top();
		pq.pop();
		if(w != dp[u]) continue;
		for(auto [v, c, p]: g[u]){
			ll w2 = w + c + d * p;
			if(w2 < dp[v]){
				dp[v] = w2;
				pq.emplace(w2, v);
			}
		}
	}
	return dp[t];
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, a, b, d;
	cin >> n >> m >> a >> b >> d;
	while(m--){
		int u, v;
		ll c1, p1, c2, p2;
		cin >> u >> v >> c1 >> p1 >> c2 >> p2;
		g[u].eb(edge{v, c1, p1});
		g[v].eb(edge{u, c2, p2});
	}
	cout << min(go(a, b, 0) + go(b, a, 0), go(a, b, d - 1) + go(b, a, d - 1));
}
