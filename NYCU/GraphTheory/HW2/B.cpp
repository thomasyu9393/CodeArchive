#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 300005;

vector<int> g[maxn];
int diameter = 0;
int dfs(int u, int lst) {
	int mx1 = 0, mx2 = 0;
	for (int v: g[u]) {
		if (v == lst) continue;
		int res = dfs(v, u);
		if (res >= mx1) {
			mx2 = mx1, mx1 = res;
		} else if (res > mx2) {
			mx2 = res;
		}
	}
	diameter = max(diameter, mx1 + mx2);
	return mx1 + 1;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].eb(b);
		g[b].eb(a);
	}
	dfs(0, 0);
	cout << diameter << '\n';
	return 0;
}

/*
10
8 5
7 4
2 6
3 9
6 8
4 1
3 10
5 10
1 2
*/