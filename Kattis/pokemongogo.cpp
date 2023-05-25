#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;
const int inf = 1000000001;

map<string, int> mp;
int cnt = 0;
int gid(string &s) {
	int res = mp[s];
	if (res) return res - 1;
	mp[s] = ++cnt;
	return cnt - 1;
}

int n, x[21], y[21];
string s[21];

int ab(int a) {
	return (a < 0 ? -a : a);
}
int calc(int a, int b) {
	return ab(x[a] - x[b]) + ab(y[a] - y[b]);
}

int dp[20][1<<15];
int go(int lst, int mask) {
	if (~dp[lst][mask]) return dp[lst][mask];
	if (__builtin_popcount(mask) == 1) return dp[lst][mask] = ab(x[lst]) + ab(y[lst]);
	int res = inf;
	int k = gid(s[lst]);
	for (int i=0; i<n; ++i) {
		int j = gid(s[i]);
		if (j == k) continue;
		if (!(mask & (1<<j))) continue;
		res = min(res, go(i, mask - (1<<k)) + calc(i, lst));
	}
	return dp[lst][mask] = res;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i=0; i<n; ++i) {
		cin >> x[i] >> y[i] >> s[i];
		gid(s[i]);
	}
	memset(dp, -1, sizeof(dp));
	int ans = inf;
	for (int i=0; i<n; ++i) {
		ans = min(ans, go(i, (1<<cnt) - 1) + ab(x[i]) + ab(y[i]));
	}
	cout << ans << '\n';
	return 0;
}