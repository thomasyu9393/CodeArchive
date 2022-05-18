#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
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
} sgt1, sgt2, sgt3;

int a[maxn];
int ql[maxn], qr[maxn], id[maxn];
ll ans[maxn];
int mp[maxn];
vector<pair<int, int>> v;
set<int> st;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
		st.insert(a[i]);
		int lst = mp[a[i]];
		v.eb(lst, i);
		mp[a[i]] = i;
		if (!lst && i > 1) {
			sgt2.upd(1, i-1, 1, 1, n, 1);
		}
	}
	int NN = st.size();
	sort(iter(v), [&](pair<int, int> i, pair<int, int> j) {
		return i.second < j.second;
	});
	for (int i=0; i<q; ++i) {
		cin >> ql[i] >> qr[i];
		id[i] = i;
	}
	sort(id, id + q, [&](int i, int j) {
		return qr[i] < qr[j];
	});
	int vc = 0, qc = 0;
	for (int i=1; i<=n; ++i) {
		mp[i] = 0;
	}
	st.clear();
	for (int R=1; R<=n; ++R) {
		int lst = mp[a[R]];
		st.insert(a[R]);
		sgt3.upd(R, R, st.size(), 1, n, 1);
		if (!lst && R > 1) {
			sgt2.upd(1, R-1, -1, 1, n, 1);
			sgt3.upd(R, R, -1, 1, n, 1);
		} else {
			sgt3.upd(lst+1, R, -1, 1, n, 1);
		}
		while (vc < v.size() && v[vc].second == R) {
			auto [l, r] = v[vc];
			sgt1.upd(l+1, r, -r+1, 1, n, 1);
			vc++;
		}
		while (qc < q && qr[id[qc]] == R) {
			int cur = id[qc];
			ll len = qr[cur] - ql[cur] + 1;
			ll w = sgt1.query(ql[cur], R, 1, n, 1);
			ll w2 = sgt2.query(ql[cur], R, 1, n, 1);
			ll w3 = sgt3.query(ql[cur], R, 1, n, 1);
			ll tmp = len * NN * R + w;
			tmp -= w2 * R; //front
			tmp -= w3 * R; //back
			ans[cur] = tmp;
			qc++;
		}
		mp[a[R]] = R;
	}
	for (int i=0; i<q; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}
