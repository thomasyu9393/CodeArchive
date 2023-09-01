#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
const int maxn = 1000050;
const ll P = 401, M = 998244353;

ll fpow(ll b, ll p, ll mod) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

ll hashes[maxn], modp[maxn];

ll hashp(string s, bool saveval) {
	ll val = 0;
	int index = 0;
	for (char c: s) {
		val = ((val * P) % M + c) % M;
		if (saveval) hashes[index++] = val;
	}
	return val;
}

void init(ll base, int exp) {
	ll b = 1;
	modp[0] = 1;
	for (int i = 0; i < exp; i++) {
		b = (b * base) % M;
		modp[i + 1] = b;
	}
}

ll subseq(int l, int r) { //[l, r]
	if (l == 0) return hashes[r];
	return ((hashes[r] - hashes[l-1] * modp[r-l+1]) % M + M) % M;
}

signed main() {
	string s;
	cin >> s;
	init(P, s.size() + 10);
	ll val = hashp(s, 1);
	for (int i = 1; i <= s.size(); ++i) {
		ll tmp = subseq(0, i - 1);
		ll v2 = tmp;
		int a = s.size() / i, b = s.size() % i;
		for (int j = 1; j < a; ++j) {
			v2 = v2 * fpow(P, i, M) % M;
			v2 = (v2 + tmp) % M;
		}
		v2 = v2 * fpow(P, b, M) % M;
		v2 = (v2 + subseq(0, b - 1)) % M;
		if (v2 == val) {
			cout << i << ' ';
		}
	}
	return 0;
}