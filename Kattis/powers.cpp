#include <iostream>
using namespace std;
#define ll long long

ll fpow(ll b, ll p, ll m) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % m;
		b = b * b % m, p >>= 1;
	}
	return res;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	ll a, b;
	cin >> a >> b;
	if (a % 2) {
		cout << 0 << '\n';
	} else {
		cout << fpow(a/2, b, a) << '\n';
	}
	return 0;
}