#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <cassert>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
using pli = pair<ll, int>;
const int maxn = 200005;
const ll INF = 1000000000000007;

vector<pair<int, int>> g[maxn];
ll dp[2][maxn]{}, sum[maxn]{};

void solve() {
	int n, m, op;
	cin >> n >> m >> op;
	for (int i = 1; i <= n; ++i) {
		g[i].clear();
		dp[0][i] = dp[1][i] = INF;
	}
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		g[v].eb(u, w);
	}
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	dp[0][1] = 0;
	pq.emplace(0, 1);
	while (pq.size()) {
		auto [w, u] = pq.top(); pq.pop();
		if (dp[0][u] != w) continue;
		for (auto [v, w2]: g[u]) {
			if (w + w2 < dp[0][v]) {
				dp[0][v] = w + w2;
				pq.emplace(w + w2, v);
			}
		}
	}
	if (op == 1) {
		for (int i = 1; i <= n; ++i) {
			cout << (dp[0][i] < INF ? dp[0][i] : -1) << " \n"[i == n];
		}
		return;
	}
	dp[1][n] = 0;
	pq.emplace(0, n);
	while (pq.size()) {
		auto [w, u] = pq.top(); pq.pop();
		if (dp[1][u] != w) continue;
		for (auto [v, w2]: g[u]) {
			if (w + w2 < dp[1][v]) {
				dp[1][v] = w + w2;
				pq.emplace(w + w2, v);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		sum[i] = dp[0][i] + dp[1][i];
		if (sum[i] < INF) {
			pq.emplace(sum[i], i);
		}
	}
	while (pq.size()) {
		auto [w, u] = pq.top(); pq.pop();
		if (sum[u] != w) continue;
		for (auto [v, w2]: g[u]) {
			if (w + w2 < sum[v]) {
				sum[v] = w + w2;
				pq.emplace(w + w2, v);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << (sum[i] < INF ? sum[i] : -1) << " \n"[i == n];
	}
}

/*
2 2
4 5 1
2 3 1
3 1 2
3 4 3
2 4 3
2 1 4
4 5 2
2 3 1
3 1 2
3 4 3
2 4 3
2 1 4

2 4
4 6 1
1 2 2
2 1 2
2 3 4
3 2 4
4 2 3
2 4 3
4 6 2
1 2 2
2 1 2
2 3 4
3 2 4
4 2 3
2 4 3
*/

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t, op;
	cin >> t >> op;
	while (t--) {
		solve();
	}
	return 0;
}