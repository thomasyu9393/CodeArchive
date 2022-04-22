#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
using namespace std;
#define ll long long
#define eb emplace_back

const int maxn = 100005;

int x[maxn], y[maxn];
int deg[maxn]{};
vector<int> g[maxn];

bitset<maxn> ok;
vector<int> query[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        cin >> x[i] >> y[i];
        g[x[i]].eb(y[i]);
        g[y[i]].eb(x[i]);
        deg[x[i]]++;
        deg[y[i]]++;
    }
    int qq = sqrt(m);
    ll ans = 0;
    for (int i=0; i<n; ++i) {
        if (deg[i] > qq) {
            ok.reset();
            for (int j: g[i]) {
                ok[j] = 1;
            }
            for (int j=0; j<m; ++j) {
                ans += (ok[x[j]] && ok[y[j]]);
            }
        } else {
            for (int j=0; j<g[i].size(); ++j) {
                for (int k=j+1; k<g[i].size(); ++k) {
                    query[g[i][j]].eb(g[i][k]);
                }
            }
        }
    }
    for (int i=0; i<n; ++i) {
        ok.reset();
        for (int j: g[i]) {
            ok[j] = 1;
        }
        for (int j: query[i]) {
            ans += ok[j];
        }
    }
    cout << (ans / 3) << '\n';
}
