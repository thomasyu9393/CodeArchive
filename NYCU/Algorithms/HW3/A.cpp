#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
#define F first
#define S second
using pli = pair<ll, int>;
const int maxn = 100005;

ll a[maxn], b[maxn];
priority_queue<pli, vector<pli>, greater<pli>> pq;

int ind[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int j = 0; j < m; ++j) {
		cin >> b[j];
	}
	for (int i = 0; i < n; ++i) {
		pq.emplace(a[i]*a[i] + a[i]*b[0] + b[0]*b[0], i);
		ind[i] = 1;
	}
	ll ans = 0;
	while (k--) {
		auto [v, u] = pq.top(); pq.pop();
		ans ^= v;
		if (ind[u] < m) {
			int y = ind[u];
			pq.emplace(a[u]*a[u] + a[u]*b[y] + b[y]*b[y], u);
			++ind[u];
		}
	}
	cout << ans << '\n';
	return 0;
}