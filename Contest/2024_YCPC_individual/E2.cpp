#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 10005;

void solve() {
	int n, w, k;
	cin >> n >> w >> k;
	vector<int> p(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> p[i];
	}
	if (w < 2 * k || w % (2 * k) != 0) {
		cout << "No\n";
		return;
	}
	w /= (2 * k);
	for (int i = 1; i <= n; ++i) {
		if (p[i]) {
			p[i] = p[i - 1] + 1;
		} else {
			p[i] = p[i - 1];
		}
	}
	pair<int, int> dp[maxn][maxn]{};
	dp[0][0] = {-1, 0};
	for (int i = 1; i <= n; ++i) {
		for (int j = p[i]; j <= w; ++j) {
			if (dp[i - 1][j - p[i]].first) {
				dp[i][j] = {i, 1};
			} else {
				dp[i][j] = {dp[i - 1][j].first, 0};
			}
		}
		for (int j = 0; j < p[i]; ++j) {
			dp[i][j] = {dp[i - 1][j].first, 0};
		}
	}
	if (dp[n][w].first == 0) {
		cout << "No\n";
	} else {
		vector<int> ans;
		int cur = w, index = n;
		while (cur > 0) {
			if (dp[index][cur].second) {
				ans.eb(dp[index][cur].first);
				cur -= p[dp[index][cur].first];
			}
			index--;
		}
		cout << "Yes\n";
		cout << ans.size() << '\n';
		for (int i: ans) cout << i << ' ';
		cout << '\n';
	}
}
/*
4 100 10
1 0 1 0

10 100 2
0 1 1 0 0 1 1 0 1 1
*/

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	solve();
	return 0;
}
