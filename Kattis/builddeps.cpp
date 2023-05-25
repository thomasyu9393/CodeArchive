#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <queue>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 100005;

map<string, int> mp;
string s[maxn];
int cnt = 0;
int gid(string &t) {
	int res = mp[t];
	if (res) return res;
	s[++cnt] = t;
	mp[t] = cnt;
	return cnt;
}

vector<int> g[maxn];
vector<int> qq;
bool vis[maxn]{};

void dfs(int u) {
	vis[u] = 1;
	for (int v: g[u]) if (!vis[v]) {
		dfs(v);
	}
	qq.eb(u);
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	cin.ignore();
	for (int i=0; i<n; ++i) {
		string t, q;
		getline(cin, t);
		stringstream ss(t);
		ss >> q;
		q.pop_back();
		int v = gid(q);
		while (ss >> q) {
			int u = gid(q);
			g[u].eb(v);
		}
	}
	string st;
	cin >> st;
	dfs(gid(st));
	for (int i = qq.size() - 1; i >= 0; --i) {
		cout << s[qq[i]] << '\n';
	}
	return 0;
}