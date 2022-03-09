#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
#define F first
#define S second
const int maxn = 200005;

struct Line {
	int l, r;
} ar[100005];
vector<int> rig[maxn];

struct BIT {
	int tr[maxn]{}, n;
	void init(int _n) {
		n = _n;
		for (int i=1; i<=n; ++i)
			tr[i] = 0;
	}
	void upd(int x, int v) {
		for (; x<n; x+=x&-x)
			tr[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x>0; x-=x&-x)
			res += tr[x];
		return res;
	}
} bit;

bool cal(int x, int n, int k) {
	priority_queue<int> pq;
	for (int i=1; i<=n; ++i) {
		int del = max(bit.query(i) - x, 0);
		for (int j: rig[i]) {
			pq.push(j);
		}
		while (del--) {
			if (pq.empty() || pq.top() <= i || (--k) < 0) return 0;
			bit.upd(i, -1);
			bit.upd(pq.top(), 1);
			pq.pop();
		}
	}
	return 1;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> v;
	for (int i=0; i<n; ++i) {
		cin >> ar[i].l >> ar[i].r;
		v.eb(ar[i].l);
		v.eb(ar[i].r);
	}
	sort(iter(v));
	v.resize(unique(iter(v)) - begin(v));
	for (int i=0; i<n; ++i) {
		auto &[l, r] = ar[i];
		l = upper_bound(iter(v), l) - begin(v);
		r = upper_bound(iter(v), r) - begin(v);
		rig[l].eb(r);
	}
	int l = 0, r = n;
	while (l < r) {
		bit.init(v.size());
		for (int i=0; i<n; ++i) {
			bit.upd(ar[i].l, 1);
			bit.upd(ar[i].r, -1);
		}
		int mid = (l + r) / 2;
		if (cal(mid, v.size(), k))
			r = mid;
		else
			l = mid + 1;
	}
	cout << l << '\n';
	return 0;
}
