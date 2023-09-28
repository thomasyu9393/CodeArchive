#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
using namespace std;
#define ll long long
#define iter(x) begin(x), end(x)
const int maxn = 200005;

ll w[maxn];
int lef[maxn], rig[maxn];
set<pair<ll, int>> st;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
		sum += w[i];
		lef[i] = i - 1, rig[i] = i + 1;
		if (i == n) rig[i] = 0;
		st.insert({w[i], -i});
	}
	for (int i = 1; i < n; ++i) {
		auto [w1, s1] = *prev(st.end());
		if (w1 > sum - w1) {
			auto [w2, s2] = *st.begin();
			auto it = st.lower_bound({w2 + 1, -maxn});
			auto [w3, s3] = *prev(it);
			w1 = w3, s1 = s3;
		}
		cout << -s1 << ' ' << w1 << '\n';
		int L = lef[-s1], R = rig[-s1];
		st.erase(st.find({w1, s1}));
		if (w1 % 2) {
			--sum;
		}
		w1 /= 2;
		if (L > 0) {
			st.erase(st.find({w[L], -L}));
			w[L] += w1;
			st.insert({w[L], -L});
			rig[L] = R;
		} else {
			sum -= w1;
		}
		if (R > 0) {
			st.erase(st.find({w[R], -R}));
			w[R] += w1;
			st.insert({w[R], -R});
			lef[R] = L;
		} else {
			sum -= w1;
		}
		w[-s1] = 0;
		lef[-s1] = rig[-s1] = 0;
	}
	auto [ff, ss] = *st.begin();
	cout << -ss << ' ' << ff << '\n';
	return 0;
}