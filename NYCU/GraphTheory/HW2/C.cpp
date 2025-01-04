#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 1000005;

vector<int> g[maxn];
int deg[maxn]{};

vector<int> verge;
int dfs1(int u, int lst, bool qq) {
	int cnt = 0;
	for (int v: g[u]) if (v != lst) {
		cnt += dfs1(v, u, qq | (deg[u] == 3));
	}
	if (deg[u] == 1) {
		return 0;
	} else if (deg[u] == 2) {
		return cnt;
	} else {
		if (cnt == 0 || (!qq && cnt == 1)) {
			verge.eb(u);
		}
		return 1;
	}
}

int key[maxn], seq[maxn];
int dfs2(int u, int lst, int t, int ind) {
	bool find_t = (u == t);
	int d[2]{}, di = -1;
	for (int v: g[u]) if (v != lst) {
		int res = dfs2(v, u, t, ind + (deg[u] == 3 ? 1 : 0));
		if (res == -1) {
			find_t = 1;
		} else {
			d[++di] = res;
		}
	}
	if (u == lst) {
		seq[0] = d[0], seq[1] = d[1];
	} else if (u == t) {
		seq[ind] = d[0], seq[ind + 1] = d[1];
	} else if (deg[u] == 3) {
		seq[ind] = d[0];
	}
	return (find_t ? -1 : d[0] + 1);
}

bool check(int m) {
	bool ok1 = 1, ok2 = 1;
	for (int i = 1; i <= m; ++i) {
		if (key[i] != seq[i]) ok1 = 0;
		if (key[i] != seq[m - i + 1]) ok2 = 0;
	}
	return (ok1 || ok2);
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].eb(b);
		g[b].eb(a);
		++deg[a], ++deg[b];
	}
	cin >> m;
	int cnt = 0, st = 0;
	for (int i = 0; i < n; ++i) if (deg[i] == 3) {
		++cnt;
		st = i;
	}
	for (int i = 1; i <= m; ++i) {
		cin >> key[i];
	}
	if (cnt != m) {
		cout << "NO\n";
		return 0;
	}
	dfs1(st, st, 0);
	dfs2(verge[0], verge[0], verge[1], 1);
	bool ok = 0;
	ok |= check(m);
	swap(seq[0], seq[1]);
	ok |= check(m);
	swap(seq[m], seq[m + 1]);
	ok |= check(m);
	swap(seq[0], seq[1]);
	ok |= check(m);
	cout << (ok ? "YES\n" : "NO\n");
	return 0;
}

/*
18
0 1
1 2
2 3
3 4
2 5
5 6
6 7
7 8
5 9
9 10
9 11
11 12
12 13
13 14
12 15
15 16
15 17
5
2 3 1 2 1


14
4 13
2 5
5 8
1 11
11 7
9 2
1 13
12 0
8 1
10 6
9 6
3 9
7 12
2
2 2
*/