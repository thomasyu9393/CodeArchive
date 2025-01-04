#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 100005;

vector<int> g[maxn];
vector<int> ap;
int D[maxn]{}, L[maxn], tn = 0;
void dfs(int u, int lst) {
	D[u] = L[u] = ++tn;
	int bad = 0, cnt = 0;
	for (int v: g[u]) {
		if (!D[v]) {
			dfs(v, u);
			++cnt;
			if (D[u] <= L[v]) bad = 1;
			L[u] = min(L[u], L[v]);
		}
		L[u] = min(L[u], D[v]);
	}
	if (u == lst && cnt < 2) bad = 0;
	if (bad) ap.eb(u);
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
	}
	dfs(1, 1);
	sort(iter(ap));
	cout << ap.size() << '\n';
	for (int i: ap) {
		cout << i << ' ';
	}
	cout << '\n';
	return 0;
}

/*
8 8
1 2
1 5
2 3
2 4
3 6
4 5
5 7
5 8

8 7
1 2
1 6
2 3
3 4
4 5
4 8
5 7

8 8
1 2
2 3
2 7
2 4
3 4
4 5
5 6
7 8
*/