#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;

struct BIT {
	int tr[maxn]{}, n;
	void init(int _n) {
		n = _n;
	}
	void upd(int x, int v) {
		for (; x>0; x-=x&-x)
			tr[x] = max(tr[x], v);
	}
	int query(int x) {
		int res = 0;
		for (; x<=n; x+=x&-x)
			res = max(res, tr[x]);
		return res;
	}
} bit;

struct Node {
	Node *l = nullptr, *r = nullptr;
	int mx = 0, ind = -1;
	Node(){}
	void pull() {
		mx = -1, ind = -1;
		if (l) mx = l->mx, ind = l->ind;
		if (r && r->mx > mx) mx = r->mx, ind = r->ind; 
	}
} *rt[maxn];
void t_insert(Node *p, int w, int l, int r, int v, int i) {
	if (w < l || r < w) return;
	if (l == r) return p->mx = v, p->ind = i, void();
	int mid = (l + r) / 2;
	if (w <= mid) {
		if (!p->l) p->l = new Node();
		t_insert(p->l, w, l, mid, v, i);
	} else {
		if (!p->r) p->r = new Node();
		t_insert(p->r, w, mid + 1, r, v, i);
	}
	p->pull();
}
void t_upd(pair<int, int> &a, pair<int, int> b) {
	if (b.first > a.first) a = b;
}
pair<int, int> t_query(Node *p, int ql, int qr, int l, int r) {
	if (ql > qr || ql > r || qr < l) return {-1, -1};
	if (ql <= l && r <= qr) return {p->mx, p->ind};
	int mid = (l + r) / 2;
	pair<int, int> res = {-1, -1};
	if (p->l) t_upd(res, t_query(p->l, ql, qr, l, mid));
	if (p->r) t_upd(res, t_query(p->r, ql, qr, mid + 1, r));
	return res;
}

map<int, int> mp;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i=1; i<=n; ++i) {
		int a;
		cin >> a;
		mp[a] = i;
	}
	int b[maxn]{}, w[maxn]{};
	for (int i=1; i<=n; ++i) {
		cin >> b[i];
		w[i] = mp[b[i]];
	}
	bit.init(n);
	int dp[maxn]{}, nxt[maxn]{};
	for (int i=0; i<=n; ++i) {
		rt[i] = new Node();
	}
	for (int i=n; i; --i) {
		dp[i] = bit.query(w[i] + 1) + 1;
		bit.upd(w[i], dp[i]);
		nxt[i] = t_query(rt[dp[i]-1], w[i] + 1, n, 1, n).second;
		t_insert(rt[dp[i]], w[i], 1, n, b[i], i);
	}
	int mx = *max_element(dp + 1, dp + n + 1);
	int s = -1;
	for (int i=1; i<=n; ++i) {
		if (dp[i] == mx && (s == -1 || b[i] > b[s])) {
			s = i;
		}
	}
	while (~s) {
		cout << b[s] << ' ';
		s = nxt[s];
	}
	return 0;
}
