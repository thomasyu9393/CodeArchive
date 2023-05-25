#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 20005;

bool dp[maxn][105]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int w, n;
		cin >> w >> n;
		for (int i=0; i<maxn; ++i) {
			for (int j=0; j<=n; ++j) {
				dp[i][j] = 0;
			}
		}
		dp[0][0] = 1;
		for (int i=1; i<=n; ++i) {
			int v;
			cin >> v;
			for (int j = maxn - 1; j >= v; --j) {
				for (int k=1; k <= i; ++k) {
					dp[j][k] |= dp[j - v][k - 1];
				}
			}
		}
		bool ok = 0;
		for (int i=w; i<maxn; ++i) {
			for (int j=1; j<=n; ++j) if (dp[i][j]) {
				cout << i << ' ' << j << '\n';
				ok = 1;
				break;
			}
			if (ok) break;
		}
	}
	return 0;
}