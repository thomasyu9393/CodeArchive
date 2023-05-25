#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define eb emplace_back
const int maxn = 2005;

int v[maxn], w[maxn];
int dp[maxn][maxn]{};
bool ok[maxn][maxn]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	while (cin >> m >> n) {
		for (int j=1; j<=m; ++j) {
			dp[0][j] = -100000000;
		}
		for (int i=1; i<=n; ++i) {
			for (int j=0; j<=m; ++j) {
				dp[i][j] = 0;
				ok[i][j] = 0;
			}
		}
		int ans = 0;
		for (int i=1; i<=n; ++i) {
			cin >> v[i] >> w[i];
			for (int j=1; j<w[i] && j<=m; ++j) {
				dp[i][j] = dp[i-1][j];
				ok[i][j] = 0;
			}
			for (int j=w[i]; j<=m; ++j) {
				if (dp[i-1][j-w[i]] + v[i] > dp[i-1][j]) {
					dp[i][j] = dp[i-1][j-w[i]] + v[i];
					ok[i][j] = 1;
				} else {
					dp[i][j] = dp[i-1][j];
				}
				ans = max(ans, dp[i][j]);
			}
		}
		vector<int> v;
		for (int j=1; j<=m; ++j) if (dp[n][j] == ans) {
			for (int i=n; i; --i) if (ok[i][j]) {
				v.eb(i - 1);
				j -= w[i];
			}
			break;
		}
		cout << v.size() << '\n';
		for (int i: v) {
			cout << i << ' ';
		}
		cout << '\n';
	}
	return 0;
}