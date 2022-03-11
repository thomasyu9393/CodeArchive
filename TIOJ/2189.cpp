#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define F first
#define S second

using pii = pair<int, int>;

const int maxn = 100005;

void upd(pii &a, int k) {
	if (k > a.F) {
		a.S = a.F;
		a.F = k;
	} else if (k < a.F && k > a.S) {
		a.S = k;
	}
}

vector<pii> g[maxn];
pii ans = {0, 0};
pii dfs(int u, int lst, int d) {
	pii x = {d, 0}, y = {0, 0};
	for (auto [v, w]: g[u]) {
		if (v == lst) continue;
		pii res = dfs(v, u, w);
		upd(ans, y.F + res.F);
		upd(ans, y.F + res.S);
		upd(ans, y.S + res.F);
		upd(x, res.F + d);
		upd(x, res.S + d);
		upd(y, res.F);
		upd(y, res.S);
	}
	return x;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i=1; i<n; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		g[a].eb(b, w);
		g[b].eb(a, w);
	}
	dfs(0, 0, 0);
	cout << ans.S << '\n';
	return 0;
}
