#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 200005;

using pii = pair<int, int>;

vector<int> g[maxn];
vector<pii> edge;
int deg[maxn]{};

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edge.eb(a, b);
        g[a].eb(b);
        g[b].eb(a);
        ++deg[a];
        ++deg[b];
    }
    if (n < 3) {
        cout << 0 << '\n';
    } else {
        int tot = n * (n - 1) * (n - 2) / 6;
        int t1 = m * (n - 2);
        int t2 = 0;
        for (int i = 1; i <= n; ++i) {
            if (deg[i] >= 2) {
                t2 += (deg[i]) * (deg[i] - 1) / 2;
            }
        }
        int k3 = 0;
        int K = sqrt(m);
        int flag[maxn]{};
        for (int i = 1; i <= n; ++i) if (deg[i] >= K) {
            // heavy vertex
            for (int j: g[i]) {
                flag[j] = i;
            }
            for (auto [a, b]: edge) {
                if (flag[a] == i && flag[b] == i) ++k3;
            }
        }
        vector<int> query[maxn];
        for (int i = 1; i <= n; ++i) if (deg[i] < K) {
            // light vertex
            for (int x = 0; x < g[i].size(); ++x) {
                for (int y = x + 1; y < g[i].size(); ++y) {
                    query[g[i][x]].eb(g[i][y]);
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j: g[i]) {
                flag[j] = i;
            }
            for (int j: query[i]) {
                if (flag[j] == i) ++k3;
            }
        }
        k3 /= 3;
        //cout << "K3: " << k3 << '\n';
        cout << (tot - t1 + t2 - k3) * 6 << '\n';
    }
    return 0;
}