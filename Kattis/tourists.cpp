#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 200005;

int n;
vector<int> g[maxn];

int pa[18][maxn], dep[maxn];
void init(int u, int lst, int d) {
	pa[0][u] = lst;
	dep[u] = d;
	for (int i=0; i<__lg(n); ++i) {
		pa[i + 1][u] = pa[i][pa[i][u]];
	}
	for (int v: g[u]) if (v != lst) {
		init(v, u, d + 1);
	}
}

int jump(int x, int d) {
	for (int i=__lg(n); i >= 0; --i) {
		if (d & (1<<i)) x = pa[i][x];
	}
	return x;
}

int query(int a, int b) {
	if (dep[a] > dep[b]) swap(a, b);
	int ra = a, rb = b;
	b = jump(b, dep[b] - dep[a]);
	if (b == a) return dep[rb] - dep[a];
	for (int i=__lg(n); i >= 0; --i) {
		if (pa[i][a] != pa[i][b]) {
			a = pa[i][a];
			b = pa[i][b];
		}
	}
	int lca = pa[0][a];
	return dep[ra] + dep[rb] - 2 * dep[lca];
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i=1; i<n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
	}
	init(1, 1, 0);
	ll ans = 0;
	for (ll i=1; i<n; ++i) {
		for (ll j=2; i * j <= n; ++j) {
			ans += query(i, i * j) + 1;
		}
	}
	cout << ans << '\n';
	return 0;
}