#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)

void solve() {
	int n, c;
	cin >> n >> c;
	vector<int> s(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
	}
	priority_queue<int> pq;
	int ok = 0, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		while (c < s[i] && pq.size()) {
			c += pq.top();
			pq.pop();
			++cnt;
		}
		if (c >= s[i]) {
			pq.emplace(s[i]);
			ok = i;
		} else {
			ok = 0;
			break;
		}
	}
	cout << (ok == n ? cnt : -1) << '\n';
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
