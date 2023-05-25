#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <set>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 100005;

int id[maxn]{}, sz[maxn]{};
ll sum[maxn]{};
set<int> st[maxn];

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m;
	while (cin >> n >> m) {
		for (int i=1; i<=n; ++i) {
			id[i] = i, sz[i] = 1;
			sum[i] = i;
			st[i].clear();
			st[i].insert(i);
		}
		while (m--) {
			int op, a, b;
			cin >> op >> a;
			if (op == 1) {
				cin >> b;
				int u = id[a], v = id[b];
				if (u == v) continue;
				if (sz[u] < sz[v]) {
					swap(u, v); //sz[u] >= sz[v]
					swap(a, b);
				}
				for (auto x: st[v]) {
					st[u].insert(x);
					id[x] = u;
				}
				st[v].clear();
				sz[u] += sz[v];
				sz[v] = 0;
				sum[u] += sum[v];
				sum[v] = 0;
			} else if (op == 2) {
				cin >> b;
				int u = id[a], v = id[b];
				if (u == v) continue;
				sum[u] -= a;
				st[u].erase(a);
				--sz[u];
				sum[v] += a;
				st[v].insert(a);
				++sz[v];
				id[a] = v;
			} else if (op == 3) {
				int u = id[a];
				cout << sz[u] << ' ' << sum[u] << '\n';
			}
		}
	}
	return 0;
}