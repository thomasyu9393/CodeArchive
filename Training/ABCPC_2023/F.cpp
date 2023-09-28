#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 100005;
const ll inf = 1000000007;

struct SGT {
	ll tr[maxn << 2];
	void init(int l, int r, int o, ll a[]) {
		if (l == r) {
			tr[o] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		init(l, mid, o<<1, a);
		init(mid + 1, r, o<<1|1, a);
		tr[o] = max(tr[o<<1], tr[o<<1|1]);
	}
	ll query(int l, int r, int ql, int qr, int o) {
		if (ql > r || qr < l) return -inf;
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

ll w[maxn], a[maxn];
ll pref[maxn]{};
ll getw(int l, int r) {
	if (l == 0) return pref[r];
	return pref[r] - pref[l - 1];
}
int lb[maxn];

void solve() {
	ll n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		w[i] = 0;
		for (int j = 0; j < s.size() / 2; ++j) {
			if (s[j] != s[s.size() - j - 1]) ++w[i];
		}
		pref[i] = pref[i - 1] + w[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (w[i] > k) {
			lb[i] = -1;
			continue;
		}
		int l = 0, r = i;
		while (r - l > 1) { //(l, r]
			int mid = (l + r) / 2;
			if (getw(mid, i) > k)
				l = mid;
			else
				r = mid;
		}
		lb[i] = r;
	}
	a[n + 1] = 0;
	for (int i = n - 1; i > 0; --i) {
		a[i] += a[i + 1];
	}
	sgt.init(1, n, 1, a);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (lb[i] == -1) continue;
		ll res = sgt.query(1, n, lb[i], i, 1);
		res -= a[i + 1];
		ans = max(ans, res);
	}
	cout << ans << '\n';
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		solve();
	}
	return 0;
}