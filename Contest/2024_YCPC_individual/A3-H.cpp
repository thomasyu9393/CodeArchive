#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)

void solve() {
	int n, m;
	cin >> n >> m;
	--m;
	vector<int> w(n + 2, 0), pref(n + 2, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
		pref[i] = pref[i - 1] + w[i];
	}
	int l = 0, r = 1000000000000009;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		bool bad = 0;
		for (int i = 1; i <= n; ++i) if (w[i] > mid) {
			bad = 1;
			break;
		}
		int cnt = m;
		int lef = 0, rig = 0; //(lef, rig]
		for (int i = 1; i <= n; ++i) {
			if (pref[i] - pref[lef] <= mid) {
				rig = i;
			} else {
				lef = i - 1;
				rig = i - 1;
				--cnt;
			}
		}
		if (bad || cnt < 0)
			l = mid;
		else
			r = mid;
	}
	int ans = r;
	l = 0, r = 1000000000000009;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		bool bad = 0;
		for (int i = 1; i <= n; ++i) if (w[i] > mid) {
			bad = 1;
			break;
		}
		int cnt = m;
		int lef = n + 1, rig = n + 1;
		for (int i = n; i > 0; --i) {
			if (pref[rig - 1] - pref[i - 1] <= mid) {
				lef = i;
			} else {
				lef = i + 1;
				rig = i + 1;
				--cnt;
			}
		}
		if (bad || cnt < 0)
			l = mid;
		else
			r = mid;
	}
	ans = min(ans, r);
	cout << ans << '\n';
}

/*
5 1
10 14 3 8 12

10 2
5 1 9 2 3 8 5 1 3 2

10 3
5 1 9 2 3 8 5 1 3 2
*/

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	solve();
	return 0;
}
