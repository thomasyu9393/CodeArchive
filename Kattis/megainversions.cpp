#include <iostream>
using namespace std;
#define ll long long
const int maxn = 100005;

struct BIT {
	int tr[maxn]{}, n;
	void init(int _n) {
		n = _n;
		for (int i=1; i<=n; ++i)
			tr[i] = 0;
	}
	int query(int x) {
		int res = 0;
		for (; x>0; x-=x&-x)
			res += tr[x];
		return res;
	}
	void upd(int x, int v) {
		for (; x<=n; x+=x&-x)
			tr[x] += v;
	}
} bit;

int a[maxn];
int lef[maxn]{}, rig[maxn]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	bit.init(n);
	for (int i=0; i<n; ++i) {
		cin >> a[i];
		lef[i] = bit.query(n - a[i]);
		bit.upd(n + 1 - a[i], 1);
	}
	bit.init(n);
	for (int i=n-1; i>=0; --i) {
		rig[i] = bit.query(a[i] - 1);
		bit.upd(a[i], 1);
	}
	ll ans = 0;
	for (int i=0; i<n; ++i) {
		ans += 1ll * lef[i] * rig[i];
	}
	cout << ans << '\n';
	return 0;
}