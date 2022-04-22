#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)

const int maxn = 100005;
const int maxm = 10005;
const ll LOL = 100000;

ll a[maxn];
vector<int> g[maxm];
ll ori[maxm]{}, add[maxm]{};

map<ll, int> mp;

inline ll cal1(int x, int y) { //O(max(x, y))
	ll h = 1ll * min(x, y) * LOL + max(x, y);
	if (mp.find(h) != mp.end()) return mp[h];
	ll res = 0;
	int i = 0, j = 0;
	while (i < g[x].size() && j < g[y].size()) {
		if (g[x][i] == g[y][j]) {
			res++;
			i++, j++;
		} else if (g[x][i] > g[y][j]) {
			j++;
		} else {
			i++;
		}
	}
	return mp[h] = res;
}
inline ll cal2(int x, int y) { //O(x lg y)
	ll h = 1ll * min(x, y) * LOL + max(x, y);
	if (mp.find(h) != mp.end()) return mp[h];
	ll res = 0;
	if (g[x].size() > g[y].size()) swap(x, y);
	for (int i: g[x]) {
		res += *lower_bound(iter(g[y]), i) == i;
	}
	return mp[h] = res;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i=1; i<=n; ++i) {
		cin >> a[i];
	}
	int sum = 0;
	for (int i=1; i<=m; ++i) {
		int s;
		cin >> s;
		sum += s;
		while (s--) {
			int x;
			cin >> x;
			g[i].eb(x);
			ori[i] += a[x];
		}
		sort(iter(g[i]));
	}
	int k = sqrt(sum);
	vector<int> qq;
	for (int i=1; i<=m; ++i) {
		if (g[i].size() > k) qq.eb(i);
	}
	while (q--) {
		string s;
		cin >> s;
		if (s[0] == 'Q') {
			int x;
			cin >> x;
			ll res = 0;
			if (g[x].size() > k) {
				res = ori[x];
				for (int i: qq) {
					if (i == x) continue;
					res += add[i] * cal1(x, i);
				}
			} else {
				for (int i: g[x]) {
					res += a[i];
				}
				for (int i: qq) {
					res += add[i] * cal2(x, i);
				}
			}
			cout << res << '\n';
		} else {
			int x, y;
			cin >> x >> y;
			if (g[x].size() > k) { //big
				add[x] += y;
				ori[x] += 1ll * y * g[x].size();
			} else { //small
				for (int i: g[x]) {
					a[i] += y;
				}
				for (int i: qq) {
					ori[i] += 1ll * y * cal2(x, i);
				}
			}
		}
	}
	return 0;
}
