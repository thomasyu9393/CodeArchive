// Sep/14/2023 01:28
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 200005;
const ll inf = 1000000007;

vector<int> v[maxn];
map<int, int> mp;
ll a[15]{};
ll sum[maxn][15]{};
bool bad[maxn]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		int c, x;
		cin >> c;
		for (int j = 0; j < c; ++j) {
			cin >> x;
			v[i].eb(x);
		}
	}
	int cnt = 0;
	for (int i = n + 1; i <= m; ++i) {
		int c, x;
		cin >> c;
		if (c) {
			for (int j = 0; j < c; ++j) {
				cin >> x;
				v[i].eb(x);
			}
		} else {
			cin >> x;
			mp[i] = ++cnt;
			a[cnt] = x;
		}
	}
	for (int i = m; i > 0; --i) {
		for (int j: v[i]) {
			if (bad[j]) {
				bad[i] = 1;
				break;
			}
			if (v[j].size()) {
				for (int k = 1; k <= cnt; ++k) {
					sum[i][k] += sum[j][k];
					if (sum[i][k] > inf) {
						bad[i] = 1;
						sum[i][k] = 0;
					}
				}
			} else {
				++sum[i][mp[j]];
			}
		}
	}
	int ans = 0;
	for (int s = 1; s < (1<<n); ++s) {
		bool ok = 1;
		ll tmp[15]{};
		for (int i = 0; i < n; ++i) if (s & (1<<i)) {
			if (bad[i + 1]) {
				ok = 0;
				break;
			}
			for (int j = 1; j <= cnt; ++j) {
				tmp[j] += sum[i + 1][j];
			}
		}
		for (int j = 1; j <= cnt; ++j) {
			if (tmp[j] > a[j]) ok = 0;
		}
		if (ok) ans = max(ans, __builtin_popcount(s));
	}
	cout << ans << '\n';
	return 0;
}