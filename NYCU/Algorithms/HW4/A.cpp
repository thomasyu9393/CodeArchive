#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
#define F first
#define S second
const int maxn = 300005;

int p[maxn];
pair<int, int> seg[maxn];
vector<int> v[maxn];

void solve() {
	int n;
	cin >> n;
	vector<int> u;
	for (int i = 0; i < n; ++i) {
		cin >> p[i];
		u.eb(p[i]);
	}
	sort(p, p + n);
	for (int i = 0; i < n; ++i) {
		cin >> seg[i].F >> seg[i].S;
		u.eb(seg[i].F);
		u.eb(seg[i].S);
	}
	sort(iter(u));
	u.resize(unique(iter(u)) - begin(u));
	for (int i = 0; i < n; ++i) {
		p[i] = upper_bound(iter(u), p[i]) - begin(u);
		seg[i].F = upper_bound(iter(u), seg[i].F) - begin(u);
		seg[i].S = upper_bound(iter(u), seg[i].S) - begin(u);
	}
	for (int i = 0; i <= p[n - 1]; ++i) {
		v[i].clear();
	}
	for (int i = 0; i < n; ++i) {
		v[seg[i].F].eb(seg[i].S);
	}
	priority_queue<int, vector<int>, greater<int>> pq;
	int cur = 0, ok = 1;
	for (int i = 0; i < n; ++i) {
		while (cur < p[i]) {
			++cur;
			for (int j: v[cur]) {
				pq.emplace(j);
			}
		}
		if (!pq.size() || pq.top() < p[i]) {
			ok = 0;
			break;
		}
		pq.pop();
	}
	cout << (ok ? "Yes\n" : "No\n");
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}