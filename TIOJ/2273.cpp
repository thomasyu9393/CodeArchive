#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 300005;

struct SegTree {
	ll tr[maxn<<2]{}, ad[maxn<<2]{};
	void push(int l, int r, int o) {
		if (!ad[o]) return;
		int mid = l + ((r-l)>>1);
		tr[o<<1] += ad[o] * (mid - l + 1);
		ad[o<<1] += ad[o];
		tr[o<<1|1] += ad[o] * (r - mid);
		ad[o<<1|1] += ad[o];
		ad[o] = 0;
	}
	ll query(int ql, int qr, int l, int r, int o) {
		if (ql <= l && r <= qr) return tr[o];
		if (ql > r || qr < l) return 0;
		int mid = l + ((r-l)>>1);
		push(l, r, o);
		return query(ql, qr, l, mid, o<<1) + query(ql, qr, mid+1, r, o<<1|1);
	}
	void upd(int ql, int qr, ll x, int l, int r, int o) {
		if (ql > r || qr < l) return;
		if (ql <= l && r <= qr) {
			tr[o] += x * (r - l + 1);
			ad[o] += x;
			return;
		}
		int mid = l + ((r-l)>>1);
		push(l, r, o);
		upd(ql, qr, x, l, mid, o<<1);
		upd(ql, qr, x, mid+1, r, o<<1|1);
		tr[o] = tr[o<<1] + tr[o<<1|1];
	}
} sgt[2];

int a[maxn], mp[maxn]{};
int ql[maxn], qr[maxn], id[maxn];
ll ans[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
	}
	for (int i=0; i<q; ++i) {
		cin >> ql[i] >> qr[i];
		id[i] = i;
	}
	sort(id, id + q, [&](int i, int j) {
		return qr[i] < qr[j];
	});
	int qc = 0;
	for (int R=1; R<=n; ++R) {
		int lst = mp[a[R]];
		sgt[0].upd(lst+1, R, -R+1, 1, n, 1);
		sgt[1].upd(lst+1, R, 1, 1, n, 1);
		while (qc < q && qr[id[qc]] == R) {
			int cur = id[qc++];
			ll w = sgt[0].query(ql[cur], R, 1, n, 1);
			ll c = sgt[1].query(ql[cur], R, 1, n, 1);
			ans[cur] = c * R + w;
		}
		if (qc == q) break;
		mp[a[R]] = R;
	}
	for (int i=0; i<q; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}
