#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define eb emplace_back
const int maxn = 200005;

struct BIT {
	int n;
	ll tr[maxn]{};
	void init(int _n) { n = _n; }
	void upd(int x, ll v) {
		for (; x <= n; x += x&-x)
			tr[x] += v;
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x&-x)
			res += tr[x];
		return res;
	}
} bit;

int v[maxn]{};
vector<int> g[maxn];
int st[maxn], ed[maxn], tn = 0;
void dfs(int u, int lst) {
	st[u] = ++tn;
	for (int v: g[u]) {
		if (v == lst) continue;
		dfs(v, u);
	}
	ed[u] = tn;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
	}
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
	}
	dfs(1, 1);
	bit.init(n);
	for (int i = 1; i <= n; ++i) {
		bit.upd(st[i], v[i]);
	}
	while (q--) {
		int op, a, b;
		cin >> op;
		if (op == 1) {
			cin >> a >> b;
			bit.upd(st[a], b - v[a]);
			v[a] = b;
		} else {
			cin >> a;
			ll ans = bit.query(ed[a]) - bit.query(st[a] - 1);
			cout << ans << '\n';
		}
	}
	return 0;
}