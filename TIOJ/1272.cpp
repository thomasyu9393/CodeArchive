#include <iostream>
#include <vector>
using namespace std;
const int maxn = 100001;

int tr[maxn<<2]{}, tag[maxn<<2]{};

void push(int l, int r, int o) {
	if (!tag[o]) return;
	int mid = (l + r) / 2;
	tr[o<<1] += tag[o] * (mid - l + 1);
	tag[o<<1] += tag[o];
	tr[o<<1|1] += tag[o] * (r - mid);
	tag[o<<1|1] += tag[o];
	tag[o] = 0;
}

void upd(int ql, int qr, int l, int r, int o) {
	if (ql > r || qr < l) {
		return;
	}
	if (ql <= l && r <= qr) {
		tr[o] += (r - l + 1);
		++tag[o];
		return;
	}
	push(l, r, o);
	int mid = (l + r) / 2;
	upd(ql, qr, l, mid, o<<1);
	upd(ql, qr, mid + 1, r, o<<1|1);
	tr[o] = tr[o<<1] + tr[o<<1|1];
}

int query(int qx, int l, int r, int o) {
	if (l == r) return tr[o];
	push(l, r, o);
	int mid = (l + r) / 2;
	if (qx > mid)
		return query(qx, mid + 1, r, o<<1|1);
	else
		return query(qx, l, mid, o<<1);
}

vector<int> g[maxn];
int in[maxn], out[maxn], tn = 0;
void dfs(int u, int lst) {
	in[u] = ++tn;
	for (int v: g[u]) {
		if (v != lst) dfs(v, u);
	}
	out[u] = tn;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i=1; i<=n; ++i) {
		int k, v;
		cin >> k;
		while (k--) {
			cin >> v;
			g[i].emplace_back(v);
		}
	}
	dfs(1, -1);
	while (m--) {
		int op, x;
		cin >> op >> x;
		if (op) {
			cout << query(in[x], 1, tn, 1) % 2 << '\n';
		} else {
			upd(in[x], out[x], 1, tn, 1);
		}
	}
	return 0;
}