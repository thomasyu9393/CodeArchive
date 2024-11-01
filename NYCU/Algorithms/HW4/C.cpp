#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 205;
const ll inf = 1000000000007;

ll ab(ll x) {
	return x < 0 ? -x : x;
}

ll w[maxn], pref[maxn]{};
ll query(int l, int r) {
	return pref[r] - pref[l - 1];
}

ll dp[maxn][maxn];
int cut[maxn][maxn];
ll go(int l, int r) {
	if (l == r) return dp[l][r] = 0;
	if (dp[l][r] != -1) return dp[l][r];
	ll mi = inf, id = -1;
	for (int mid = l; mid < r; ++mid) {
		ll tmp = go(l, mid) + go(mid + 1, r);
		tmp += ab(query(l, mid) - query(mid + 1, r));
		if (tmp < mi) {
			mi = tmp;
			id = mid;
		}
	}
	cut[l][r] = id;
	return dp[l][r] = mi;
}

vector<int> ans;
void qq(int l, int r) {
	if (l == r) return;
	ans.eb(cut[l][r]);
	qq(l, cut[l][r]);
	qq(cut[l][r] + 1, r);
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	ll lst = 0;
	for (int i = 1; i <= n; ++i) {
		ll x;
		cin >> x;
		w[i] = x - lst;
		pref[i] = pref[i - 1] + w[i];
		lst = x;
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = -1;
		}
	}
	cout << go(1, n) << '\n';
	qq(1, n);
	for (int i: ans) {
		cout << i << ' ';
	}
	return 0;
}