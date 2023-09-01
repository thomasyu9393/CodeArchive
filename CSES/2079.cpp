#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define eb emplace_back
const int maxn = 200005;

int n;
vector<int> g[maxn];
int sz[maxn]{};

void dfs(int u, int lst) {
	sz[u] = 1;
	for (int v: g[u]) {
		if (v == lst) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int findcentroid(int u, int lst) {
	for (int v: g[u]) {
		if (v == lst) continue;
		if (2 * sz[v] >= n) return findcentroid(v, u);
	}
	return u;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
	}
	dfs(1, 1);
	int ans = findcentroid(1, 1);
	cout << ans << '\n';
	return 0;
}