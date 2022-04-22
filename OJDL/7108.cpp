#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005;

struct Node {
	int tr[N<<1]{}, n;
	void upd(int x, int v) {
		for (tr[x+=n]+=v; x>1; x>>=1)
			tr[x>>1] = tr[x] + tr[x^1];
	}
	int query(int l, int r) { //[l, r)
		int res = 0;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1){
			if (l & 1) res += tr[l++];
			if (r & 1) res += tr[--r];
		}
		return res;
	}
} sgt1, sgt2;

vector<int> a, b;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	a.resize(n);
	for (int &i: a) {
		cin >> i;
		b.emplace_back(i);
	}
	if (n == 1) {
		cout << "0\n";
		return 0;
	}
	sort(b.begin(), b.end());
	b.resize(unique(b.begin(), b.end()) - b.begin());
	for (int &i: a) {
		i = lower_bound(b.begin(), b.end(), i) - b.begin();
	}
	sgt1.n = n, sgt2.n = n;
	int ans = 0;
	sgt1.upd(a[n-1], b[a[n-1]]);
	sgt2.upd(a[n-1], 1);
	for (int i=n-2; ~i; --i) {
		ans += 2 * (sgt1.query(a[i] + 1, n) - b[a[i]] * sgt2.query(a[i] + 1, n));
		ans += b[a[i]] * sgt2.query(0, a[i]) - sgt1.query(0, a[i]);
		sgt1.upd(a[i], b[a[i]]);
		sgt2.upd(a[i], 1);
	}
	cout << ans << '\n';
	return 0;
}
