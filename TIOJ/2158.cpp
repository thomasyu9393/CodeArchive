#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
#define F first
#define S second

const int maxn = 2005;
inline int ab(int x) {return x < 0 ? -x : x;}

pair<int, int> a[maxn], b[maxn];
int val[maxn]{};
inline int calc(int x, int y) { //x: a, y: b
	return max(ab(a[x].F - b[y].F), ab(a[x].S - b[y].S));
}

struct QQ {
	int u, v, d;
	QQ(int u, int v, int d): u(u), v(v), d(d){}
	bool operator<(const QQ& p) const {
		return d < p.d;
	}
};
vector<QQ> dis;
int go[maxn], cnt[maxn]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i=0; i<n; ++i) {
		cin >> a[i].F >> a[i].S >> val[i];
	}
	for (int i=0; i<m; ++i) {
		cin >> b[i].F >> b[i].S;
		go[i] = -1;
	}
	for (int j=0; j<m; ++j) {
		for (int i=0; i<n; ++i) {
			dis.eb(QQ{j, i, calc(i, j)});
		}
	}
	sort(iter(dis));
	int ans = 0, cur = 0;
	int lst = -1;
	for (auto [u, v, d]: dis) {
		if (d != lst) ans = max(ans, cur);
		if (go[u] < 0 || val[v] > val[go[u]]) {
			if (~go[u]) {
				cnt[go[u]]--;
				if (!cnt[go[u]]) cur--;
			}
			go[u] = v;
			cnt[v]++;
			if (cnt[v] == 1) cur++;
		}
		lst = d;
	}
  ans = max(ans, cur);
	cout << ans << '\n';
	return 0;
}
