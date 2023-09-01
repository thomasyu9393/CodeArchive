#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define eb emplace_back
const int maxn = 200005;

int n, k;
vector<int> g[maxn];
int sz[maxn]{};
bool ok[maxn]{};

int get_subtree_size(int u, int lst) {
	sz[u] = 1;
	for (int v: g[u]) {
		if (v == lst || ok[v]) continue;
		sz[u] += get_subtree_size(v, u);
	}
	return sz[u];
}

int get_centroid(int u, int lst, int tree_size) {
	for (int v: g[u]) {
		if (v == lst || ok[v]) continue;
		if (2 * sz[v] >= tree_size) {
			return get_centroid(v, u, tree_size);
		}
	}
	return u;
}

int cnt[maxn]{1}, tmp;
ll ans = 0;

void dfs(int u, int lst, int d, bool filling) {
	if (d > k) return;
	if (filling) {
		++cnt[d];
		tmp = max(tmp, d);
	} else {
		ans += cnt[k - d];
	}
	for (int v: g[u]) {
		if (v == lst || ok[v]) continue;
		dfs(v, u, d + 1, filling);
	}
}

void centroid_decomp(int u = 1) {
	int centroid = get_centroid(u, u, get_subtree_size(u, u));
	ok[centroid] = 1;
	tmp = 0;
	for (int v: g[centroid]) if (!ok[v]) {
		dfs(v, centroid, 1, 0);
		dfs(v, centroid, 1, 1);
	}
	for (int i = 1; i <= tmp; ++i) {
		cnt[i] = 0;
	}
	for (int v: g[centroid]) if (!ok[v]) {
		centroid_decomp(v);
	}
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
	}
	centroid_decomp(1);
	cout << ans << '\n';
	return 0;
}