// Sep/20/2023 14:36
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <set>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 10005;

struct BIT {
	int tr[maxn]{}, n;
	void init(int _n) { n = _n; }
	void upd(int x, int v) {
		for (; x <= n; x += x&-x)
			tr[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x&-x)
			res += tr[x];
		return res;
	}
	int query_k(int x, int k) {
		int l = x - 1, r = n;
		while (r - l > 1) { //(l, r]
			int mid = (l + r) / 2;
			if (query(mid) - query(x - 1) < k)
				l = mid;
			else
				r = mid;
		}
		if (query(r) - query(r - 1) > 0)
			return r;
		return -1;
	}
} bit;

int ki[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	bit.init(n);
	for (int i = 1; i <= n; ++i) {
		cin >> ki[i];
		bit.upd(i, 1);
	}
	int cur = 1, m = n;
	while (m > 1) {
		int need = ki[cur] % m;
		if (need == 0) need = m;
		int rear = bit.query(n) - bit.query(cur - 1);
		if (rear >= need) {
			int bye = bit.query_k(cur, need);
			bit.upd(bye, -1);
			cur = bit.query_k(bye, 1);
			if (cur < 0) cur = bit.query_k(1, 1);
		} else {
			int bye = bit.query_k(1, need - rear);
			bit.upd(bye, -1);
			cur = bit.query_k(bye, 1);
			if (cur < 0) cur = bit.query_k(1, 1);
		}
		--m;
	}
	cout << cur << '\n';
	return 0;
}