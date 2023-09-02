#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 200005;

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
	int find_p(int p) {
		int l = 0, r = n;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (query(mid) < p)
				l = mid;
			else
				r = mid;
		}
		return r;
	}
} bit;

int a[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	bit.init(n);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		bit.upd(i, 1);
	}
	for (int i = 1; i <= n; ++i) {
		int p;
		cin >> p;
		int w = bit.find_p(p);
		cout << a[w] << ' ';
		bit.upd(w, -1);
	}
	return 0;
}