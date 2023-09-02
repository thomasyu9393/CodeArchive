#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 200005;
const ll mod = 1000000007;

struct BIT {
	int n;
	ll tr[maxn]{};
	void init(int _n) { n = _n; }
	void upd(int x, ll v) {
		for (; x <= n; x += x&-x)
			tr[x] = (tr[x] + v) % mod;
	}
	ll query(int x) {
		ll res = 0;
		for (; x > 0; x -= x&-x)
			res = (res + tr[x]) % mod;
		return res;
	}
} bit;

int a[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	vector<int> b;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		b.eb(a[i]);
	}
	sort(iter(b));
	b.resize(unique(iter(b)) - begin(b));
	bit.init(n);
	for (int i = 1; i <= n; ++i) {
		int x = upper_bound(iter(b), a[i]) - begin(b);
		bit.upd(x, bit.query(x - 1) + 1);
	}
	cout << bit.query(n) << '\n';
	return 0;
}