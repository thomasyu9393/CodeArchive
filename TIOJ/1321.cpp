#include <iostream>
using namespace std;
#define ll long long
const ll P = 53;
const ll mod = 1000000007;

ll hashv[2000005][2]{}, qq = 1;
ll get1(int l, int r) {
	if (!l) return hashv[r][0];
	return ((hashv[r][0] - hashv[l-1][0] * qq) % mod + mod) % mod;
}
ll get2(int l, int r) {
	return ((hashv[l][1] - hashv[r+1][1] * qq) % mod + mod) % mod;
}

int ans2[1000005];
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s;
	cin >> s;
	s += s;
	int n = s.size();
	ll v1 = 0, v2 = 0;
	for (int i=0; i<n; ++i) {
		v1 = (v1 * P + s[i]) % mod;
		hashv[i][0] = v1;
		v2 = (v2 * P + s[n - i - 1]) % mod;
		hashv[n - i - 1][1] = v2;
	}
	int ans = 0;
	n /= 2;
	for (int i=0; i<n; ++i) {
		qq = (qq * P) % mod;
	}
	for (int i=0; i<n; ++i) {
		ll pref = get1(i, i + n - 1);
		ll suf = get2(i, i + n - 1);
		if (pref == suf) ans2[ans++] = i;
	}
	if (!ans) {
		cout << "none\n";
	} else {
		cout << ans << ':';
		for (int i=0; i<ans; ++i) {
			cout << ' ' << ans2[i];
		}
		cout << '\n';
	}
	return 0;
}
