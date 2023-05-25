#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int mod = 9901;

int fpow(int b, int p) {
	int res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

int dp[11][2048]{};
bool ok[11][11];

int calc(int u, int n) {
	memset(dp, 0, sizeof(dp));
	dp[u][1<<u] = 1;
	for (int i=2; i<=n; ++i) {
		for (int s=1; s<(1<<n); ++s) {
			if (!(s & (1<<u))) continue;
			if (__builtin_popcount(s) != i) continue;
			for (int j=0; j<n; ++j) if (s & (1<<j)) {
				for (int k=0; k<n; ++k) if ((s & (1<<k)) && ok[k][j]) {
					dp[j][s] += dp[k][s - (1<<j)];
					dp[j][s] %= mod;
				}
			}
		}
	}
	int res = 0;
	for (int i=0; i<n; ++i) {
		if (!ok[i][u]) continue;
		res = (res + dp[i][(1<<n)-1]) % mod;
	}
	return res;
}

void solve() {
	int n, k;
	cin >> n >> k;
	memset(ok, 1, sizeof(ok));
	while (k--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ok[a][b] = ok[b][a] = 0;
	}
	for (int i=0; i<n; ++i) {
		ok[i][i] = 0;
	}
	int ans = 0;
	for (int i=0; i<n; ++i) {
		ans = (ans + calc(i, n)) % mod;
	}
	cout << (ans * fpow(2 * n, mod - 2)) % mod << '\n';
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	for (int i=1; i<=t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}