#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define F first
#define S second
#define eb emplace_back
#define iter(x) begin(x), end(x)

const ll mod = 998244353;
const int maxn = 3005;

pair<ll, ll> extgcd(ll a, ll b) {
	if (!b) return {1, 0};
	pair<ll, ll> res = extgcd(b, a % b);
	return {res.S, res.F - (a/b) * res.S};
}

ll fac[maxn]{}, facinv[maxn];
ll C(int n, int m) {
	if (n < m) return 0;
	if (m == 0 || n == m) return 1;
	return fac[n] * facinv[n-m] % mod * facinv[m] % mod;
}

struct BIT {
	ll tr[6100]{}, n;
	void init(int _n) {
		n = _n;
		for (int i=1; i<=n; ++i) tr[i] = 0;
	}
	void upd(int x, ll v) {
		for (; x<=n; x+=x&-x)
			tr[x] = (tr[x] + v) % mod;
	}
	ll query(int x) {
		ll res = 0;
		for (; x>0; x-=x&-x)
			res += tr[x];
		return res % mod;
	}
} bit;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	fac[0] = 1;
	for (int i=1; i<maxn; ++i) {
		fac[i] = fac[i-1] * i % mod;
		ll inv = extgcd(fac[i], mod).F;
		facinv[i] = (inv % mod + mod) % mod;
	}
	int n, m, k;
	int a[maxn], b[maxn];
	vector<int> v;
	cin >> n >> m >> k;
	for (int i=0; i<n; ++i) {
		cin >> a[i];
		v.eb(a[i]);
	}
	sort(a, a + n);
	for (int j=0; j<m; ++j) {
		cin >> b[j];
		v.eb(b[j]);
	}
	sort(b, b + m);
	sort(iter(v));
	v.resize(unique(iter(v)) - begin(v));
	for (int i=0; i<n; ++i) a[i] = upper_bound(iter(v), a[i]) - begin(v);
	for (int j=0; j<m; ++j) b[j] = upper_bound(iter(v), b[j]) - begin(v);
	ll A = 0;
	for (int r=1; r<=k; ++r) {
		bit.init(n + m);
		for (int j=0; j<m; ++j) {
			bit.upd(b[j], C(j, r-1) * C(m-j-1, k-r) % mod);
		}
		for (int i=0; i<n; ++i) {
			A += (C(i, r-1) * C(n-i-1, k-r) % mod) * bit.query(a[i]-1) % mod;
			A %= mod;
		}
	}
	if (A) {
		ll inv = extgcd(C(n, k) * C(m, k) % mod, mod).F;
		inv = (inv % mod + mod) % mod;
		cout << (A * inv % mod) << '\n';
	} else {
		cout << "0\n";
	}
	return 0;
}
