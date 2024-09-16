#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 50005;

vector<int> g[maxn];
int indeg[maxn]{};
int dp[maxn]{}, cnt[maxn]{};

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	while (m--) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		++indeg[b];
	}
	for (int i = 1; i <= n; ++i) {
		cnt[i] = maxn;
	}
	queue<pair<int, int>> qu;
	for (int i = 1; i <= n; ++i) {
		if (indeg[i] == 0) {
			dp[i] = 1;
			cnt[i] = k;
			qu.emplace(i, k);
		}
	}
	while (qu.size()) {
		auto [u, w] = qu.front();
		qu.pop();
		for (int v: g[u]) {
			int new_a = dp[u] + (w == 1 ? 1 : 0);
			if (new_a > dp[v]) {
				dp[v] = new_a;
				cnt[v] = (w == 1 ? k : w - 1);
			} else if (new_a == dp[v]) {
				cnt[v] = min(cnt[v], (w == 1 ? k : w - 1));
			}
			--indeg[v];
			if (indeg[v] == 0) {
				qu.emplace(v, cnt[v]);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, dp[i]);
	}
	cout << ans << '\n';
}
/*
10 9 2
9 2
8 6
8 10
10 4
8 7
7 9
9 1
1 5
6 3
*/

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	solve();
	return 0;
}
