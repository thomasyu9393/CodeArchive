#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 205;

int a[maxn];
int dp[maxn], prv[maxn];

int tmp[maxn][maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	while (cin >> n) {
		if (n == 0) break;
		for (int i=0; i<n; ++i) {
			cin >> a[i];
			dp[i] = 1, prv[i] = -1;
			int mx = 1;
			for (int j=0; j<i; ++j) if (a[j] < a[i]) {
				mx = max(mx, dp[j] + 1);
			}
			dp[i] = mx;
			int ls = a[i], id = -1;
			for (int j=0; j<i; ++j) if (dp[j] + 1 == dp[i]) {
				if (a[j] < ls) {
					ls = a[j];
					id = j;
				}
			}
			prv[i] = id;
		}
		int ans = 0;
		for (int i=0; i<n; ++i) {
			ans = max(ans, dp[i]);
		}
		cout << ans;
		int cnt = 0;
		for (int i=0; i<n; ++i) if (dp[i] == ans) {
			int j = ans - 1, ptr = i;
			while (j >= 0) {
				tmp[cnt][j] = a[ptr];
				--j, ptr = prv[ptr];
			}
			++cnt;
		}
		bool nok[maxn]{};
		for (int j=0; j<ans; ++j) {
			int mi = 100000001;
			for (int i=0; i<cnt; ++i) if (!nok[i]) {
				mi = min(mi, tmp[i][j]);
			}
			for (int i=0; i<cnt; ++i) {
				if (tmp[i][j] != mi) nok[i] = 1;
			}
		}
		for (int i=0; i<cnt; ++i) if (!nok[i]) {
			for (int j=0; j<ans; ++j) {
				cout << ' ' << tmp[i][j];
			}
			cout << '\n';
			break;
		}
	}
	return 0;
}