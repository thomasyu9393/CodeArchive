#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 1000005;

int ar[maxn], lef[maxn];
bool cnt[100005]{};
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> n >> k;
	int cur = 1;
	for (int i=1; i<=n; ++i) {
		cin >> ar[i];
		while (cur < i && cnt[ar[i]]) {
			cnt[ar[cur]] = 0;
			cur++;
		}
		cnt[ar[i]] = 1;
		lef[i] = cur;
	}
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=k; ++j) {
			dp[i][j] = max(dp[i-1][j], dp[lef[i]-1][j-1] + i - lef[i] + 1);
		}
	}
	cout << dp[n][k] << '\n';
	return 0;
}
