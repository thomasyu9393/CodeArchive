#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
const int maxn = 200005;

struct BIT {
	int tr[maxn]{}, n;
	void init(int _n) {n = _n;}
	void upd(int x, int v) {
		for (; x<=n; x+=x&-x)
			tr[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x>0; x-=x&-x)
			res += tr[x];
		return res;
	}
} bit;

map<int, int> mp;
int a[maxn], ans[maxn];
vector<pair<int, int>> v[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, q;
	cin >> n >> q;
	bit.init(n);
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
	}
	for (int i=0; i<q; ++i) {
		int l, r;
		cin >> l >> r;
		v[l].eb(r, i);
	}
	for (int i=n; i; --i) {
		int lst = mp[a[i]];
		if (lst) bit.upd(lst, -1);
		bit.upd(i, 1);
		mp[a[i]] = i;
		for (auto [r, j]: v[i]) {
			ans[j] = bit.query(r);
		}
	}
	for (int i=0; i<q; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}
