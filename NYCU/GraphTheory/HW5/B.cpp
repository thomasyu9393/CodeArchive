#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 170;
const int inf = 100000007;

struct MaxFlow {
	struct edge {
		int to, cap, flow, rev;
		edge(int v, int c, int f, int r):
			to(v), cap(c), flow(f), rev(r){}
	};
	vector<edge> g[maxn];
	int dis[maxn], cur[maxn];
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
	}
	void reset(int n) {
		for (int i = 1; i <= n; ++i) {
			for (auto &e: g[i]) e.flow = 0;
		}
	}
	void addEdge(int u, int v, int c) {
		edge a = edge(v, c, 0, (int)g[v].size());
		edge b = edge(u, 0, 0, (int)g[u].size());
		g[u].eb(a);
		g[v].eb(b);
	}
	bool bfs(int s, int t) {
		memset(dis, -1, sizeof(dis));
		queue<int> qu;
		dis[s] = 0;
		qu.emplace(s);
		while (qu.size()) {
			int u = qu.front();
			qu.pop();
			for (auto &e: g[u]) {
				if (dis[e.to] == -1 && e.cap > e.flow) {
					dis[e.to] = dis[u] + 1;
					qu.emplace(e.to);
				}
			}
		}
		return (dis[t] != -1);
	}
	int dfs(int u, int t, int df) {
		if (u == t || df == 0) return df;
		for (int &i = cur[u]; i < (int)g[u].size(); ++i) {
			edge &e = g[u][i];
			if (dis[e.to] == dis[u] + 1 && e.cap > e.flow) {
				int sf = dfs(e.to, t, min(df, e.cap - e.flow));
				if (sf > 0) {
					e.flow += sf;
					g[e.to][e.rev].flow -= sf;
					return sf;
				}
			}
		}
		dis[u] = -1;
		return 0;
	}
	int Dinic(int s, int t) {
		int flow = 0;
		while (bfs(s, t)) {
			memset(cur, 0, sizeof(cur));
			while (int df = dfs(s, t, inf)) {
				flow += df;
			}
		}
		return flow;
	}
} mxflow;

vector<pair<int, int>> edges;
bool mp[maxn][maxn]{};

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		edges.eb(a, b);
		mp[a][b] = mp[b][a] = 1;
	}
	int ans = n - 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			//i: source; j: sink
			//number of vertex-disjoint i-j paths
			//-> max flow with vertex capacity 1
			mxflow.init(n * 2);
			for (auto &[a, b]: edges) {
				if ((a == i && b == j) || (a == j && b == i)) {
					mxflow.addEdge(a, b, 1);
					mxflow.addEdge(b, a, 1);
				} else if (a == i || a == j) {
					mxflow.addEdge(a, b, 1);
					mxflow.addEdge(b * 2, a, 1);
				} else if (b == i || b == j) {
					mxflow.addEdge(b, a, 1);
					mxflow.addEdge(a * 2, b, 1);
				} else {
					mxflow.addEdge(a * 2, b, 1);
					mxflow.addEdge(b * 2, a, 1);
				}
			}
			for (int v = 1; v <= n; ++v) {
				if (v == i || v == j) continue;
				mxflow.addEdge(v, v * 2, 1); //v_in -> v_out
			}
			int res = mxflow.Dinic(i, j);
			ans = min(ans, res);
		}
	}
	cout << ans << '\n';
	return 0;
}

/*
4 4
1 2
2 3
3 4
4 1

4 6
1 2
1 3
1 4
2 3
2 4
3 4
*/