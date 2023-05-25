#include <iostream>
using namespace std;
#define ll long long
const int maxn = 91;

ll dp[maxn]{};

bool go(ll n, ll k) {
	if (n <= 2) {
		return (n == 1);
	}
	if (n == 3) {
		return (k == 1);
	}
	if (n >= 90 || k <= dp[n-2]) {
		return go(n-2, k);
	}
	if (k <= dp[n-2] + dp[n-3]) {
		return go(n-3, k - dp[n-2]);
	}
	return go(n-2, k - dp[n-2] - dp[n-3]);
}

signed main() {
	dp[1] = dp[2] = 1;
	for (int i=3; i<maxn; ++i) {
		dp[i] = dp[i-2] + dp[i-1];
	}
	ll n, k;
	cin >> n >> k;
	cout << (go(n, k) ? 'N' : 'A') << '\n';
	return 0;
}