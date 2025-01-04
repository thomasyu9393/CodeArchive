#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 2005;
const int inf = 1000000005;

struct MaxFlow {
	struct edge {
		int v, c, f, rev;
		edge(int v, int c, int f, int r): v(v), c(c), f(f), rev(r){}
	};
	vector<edge> g[maxn];
	int dis[maxn], cur[maxn];
	void addEdge(int u, int v, int c) {
		edge a{v, c, 0, (int)g[v].size()};
		edge b{u, 0, 0, (int)g[u].size()};
		g[u].eb(a);
		g[v].eb(b);
	}
	bool bfs(int s, int t) {
		memset(dis, -1, sizeof(dis));
		queue<int> qu;
		qu.emplace(s);
		dis[s] = 0;
		while (qu.size()) {
			int u = qu.front();
			qu.pop();
			for (auto [v, c, f, r]: g[u]) {
				if (dis[v] == -1 && c > f) {
					dis[v] = dis[u] + 1;
					qu.emplace(v);
				}
			}
		}
		return dis[t] != -1;
	}
	int dfs(int u, int t, int sf) {
		if (u == t || sf == 0) return sf;
		for (int &i = cur[u]; i < g[u].size(); ++i) {
			auto &[v, c, f, r] = g[u][i];
			if (dis[v] == dis[u] + 1 && c > f) {
				int tmp = dfs(v, t, min(c - f, sf));
				if (tmp > 0) {
					f += tmp;
					g[v][r].f -= tmp;
					return tmp;
				}
			}
		}
		return 0;
	}
	int dinic(int s, int t) {
		int flow = 0;
		while (bfs(s, t)) {
			memset(cur, 0, sizeof(cur));
			while (int sf = dfs(s, t, inf)) {
				flow += sf;
			}
		}
		return flow;
	}
} mxflow;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		int t;
		cin >> t;
		while (t--) {
			int x;
			cin >> x;
			mxflow.addEdge(i, n + x, 2); //hero to monster
		}
		mxflow.addEdge(0, i, 1); //source to hero
		mxflow.addEdge(n + m + 1, i, 1); //potion to hero
	}
	mxflow.addEdge(0, n + m + 1, k); //source to potion
	for (int i = 1; i <= m; ++i) {
		mxflow.addEdge(n + i, n + m + 2, 1); //monster to sink
	}
	cout << mxflow.dinic(0, n + m + 2) << '\n';
	return 0;
}

/*
3 5 2
4 1 2 3 5
2 2 5
2 1 2

5 10 2
2 3 10
5 1 3 4 6 10
5 3 4 6 8 9
3 1 9 10
5 1 3 6 7 10

5 6 1
6 1 2 3 4 5 6
1 1
1 1
1 1
1 1

6 6 1
6 1 2 3 4 5 6
6 1 2 3 4 5 6
6 1 2 3 4 5 6
1 1
1 1
1 1
*/