#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)

vector<ll> a, b;
vector<ll> sa, sb;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	ll n, x, t;
	cin >> n >> x;
	for (int i = 0; i < n/2; ++i) {
		cin >> t;
		a.eb(t);
	}
	for (int i = n/2; i < n; ++i) {
		cin >> t;
		b.eb(t);
	}
	ll ans = 0;
	n = a.size();
	for (int i = 1; i < (1<<n); ++i) {
		ll sum = 0;
		for (int j = 0; j < n; ++j) if (i & (1<<j)) {
			sum += a[j];
		}
		if (sum < x)
			sa.eb(sum);
		else if (sum == x)
			++ans;
	}
	n = b.size();
	for (int i = 1; i < (1<<n); ++i) {
		ll sum = 0;
		for (int j = 0; j < n; ++j) if (i & (1<<j)) {
			sum += b[j];
		}
		if (sum < x)
			sb.eb(sum);
		else if (sum == x)
			++ans;
	}
	sort(iter(sa));
	sort(iter(sb));
	for (ll i: sa) {
		ans += upper_bound(iter(sb), x - i) - lower_bound(iter(sb), x - i);
	}
	cout << ans << '\n';
	return 0;
}