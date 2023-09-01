#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 200005;

struct SegTree {
	int tr[maxn << 2];
	void init(int l, int r, int o, int a[]) {
		if (l == r) {
			tr[o] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		init(l, mid, o<<1, a);
		init(mid + 1, r, o<<1|1, a);
		tr[o] = max(tr[o<<1], tr[o<<1|1]);
	}
	void upd(int l, int r, int p, int v, int o) {
		if (l == r) {
			tr[o] = v;
			return;
		}
		int mid = (l + r) / 2;
		if (p <= mid)
			upd(l, mid, p, v, o<<1);
		else
			upd(mid + 1, r, p, v, o<<1|1);
		tr[o] = max(tr[o<<1], tr[o<<1|1]);
	}
	int query(int l, int r, int ql, int qr, int o) {
		if (ql > r || qr < l) return 0;
		if (ql <= l && r <= qr) return tr[o];
		int mid = (l + r) / 2;
		if (qr <= mid)
			return query(l, mid, ql, qr, o<<1);
		else if (ql > mid)
			return query(mid + 1, r, ql, qr, o<<1|1);
		else
			return max(query(l, mid, ql, qr, o<<1), query(mid + 1, r, ql, qr, o<<1|1));
	}
} sgt;

vector<int> g[maxn];

int dep[maxn], pa[maxn], sz[maxn], nxt[maxn];
int id[maxn], rt[maxn];

int dfs(int u, int lst, int d = 0) {
	dep[u] = d;
	pa[u] = lst;
	sz[u] = 1;
	nxt[u] = -1;
	for (int v: g[u]) {
		if (v == lst) continue;
		sz[u] += dfs(v, u, d + 1);
		if (nxt[u] == -1 || sz[v] > sz[nxt[u]]) {
			nxt[u] = v;
		}
	}
	return sz[u];
}

int tn = 0;
void mapId(int u, int lst, int root) {
	id[u] = ++tn;
	rt[u] = root;
	if (~nxt[u]) mapId(nxt[u], u, root);
	for (int v: g[u]) {
		if (v == lst || v == nxt[u]) continue;
		mapId(v, u, v);
	}
}

int val[maxn]{};
int tmp[maxn]{};

int solve(int a, int b, int n) {
	int ans = 0;
	while (rt[a] != rt[b]) {
		if (dep[rt[a]] > dep[rt[b]]) swap(a, b);
		int res = sgt.query(1, n, id[rt[b]], id[b], 1);
		ans = max(ans, res);
		b = pa[rt[b]];
	}
	if (a != b) {
		if (id[a] > id[b]) swap(a, b);
		int res = sgt.query(1, n, id[a], id[b], 1);
		ans = max(ans, res);
	} else {
		ans = max(ans, tmp[id[a]]);
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> val[i];
	}
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
	}
	dfs(1, 1);
	mapId(1, 1, 1);
	for (int i = 1; i <= n; ++i) {
		tmp[id[i]] = val[i];
	}
	sgt.init(1, n, 1, tmp);
	while (q--) {
		int op, a, b;
		cin >> op >> a >> b;
		if (op == 1) {
			sgt.upd(1, n, id[a], b, 1);
			tmp[id[a]] = b;
		} else {
			int ans = solve(a, b, n);
			cout << ans << ' ';
		}
	}
	return 0;
}