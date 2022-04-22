#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
 
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
 
const int maxn = 50005;
const int maxm = 100005;
 
struct DSU{
    int pa[maxn], sz[maxn], n;
    void init(int _n) {
        n = _n;
        for (int i=1; i<=n; ++i) {
            pa[i] = i;
            sz[i] = 1;
        }
    }
    int query(int o) {
        return o == pa[o] ? o : query(pa[o]);
    }
    int query_size(int o) {
        return sz[query(o)];
    }
    void Union(int a, int b) {
        a = query(a);
        b = query(b);
        if (a == b) return;
        if (sz[a] > sz[b]) {
            pa[b] = a;
            sz[a] += sz[b];
        } else {
            pa[a] = b;
            sz[b] += sz[a];
        }
    }
    void get(vector<pair<int, int>>& v, vector<int> p) {
        v.clear();
        for (int i: p) {
            v.eb(pa[i], sz[i]);
        }
    }
    void re(vector<pair<int, int>>& v, vector<int> p) {
        while (p.size()) {
            pa[p.back()] = v.back().first;
            sz[p.back()] = v.back().second;
            p.pop_back();
            v.pop_back();
        }
    }
} dsu;
 
struct edge{
    int a, b, w;
} e[maxm];
int ne[maxm];
 
struct task{
    int op, x, w;
} z[maxm];
 
int ans[maxm];
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m, q;
    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }
    cin >> q;
    for (int i=0; i<q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        z[i] = {a, (a == 1 ? b-1 : b), c};
        ans[i] = -1;
    }
    int k = 800;
    vector<pair<int, int>> undo;
    for (int t=0; t*k<q; ++t) {
        bool ok1[maxn]{}; //V is changed
        bool ok2[maxm]{}; //E is changed
        vector<int> upd, ques; //Z-index
        vector<int> used, nused; //E-index
        for (int i=t*k, j=(t+1)*k; i<j && i<q; ++i) {
            if (z[i].op == 1) {
                ok2[z[i].x] = 1;
                upd.eb(i);
            }
            else ques.eb(i);
        }
        for (int i=0; i<m; ++i) {
            if (ok2[i]) {
            	ok1[e[i].a] = ok1[e[i].b] = 1;
                used.eb(i);
            }
            else nused.eb(i);
        }
        vector<int> qq;
        for (int j=1; j<=n; ++j) {
        	if (ok1[j]) qq.eb(j);
        }
        sort(iter(nused), [&](int a, int b) {
            return e[a].w > e[b].w;
        });
        sort(iter(ques), [&](int a, int b){
            return z[a].w > z[b].w;
        });
        dsu.init(n);
        int indj = 0;
        for (int i: ques) {
            auto [op, s, w] = z[i];
            for (; indj<nused.size() && e[nused[indj]].w >= w; ++indj) {
                dsu.Union(e[nused[indj]].a, e[nused[indj]].b);
            }
            vector<int> qqq;
            for (int i: qq) {
                qqq.eb(dsu.query(i));
            }
            dsu.get(undo, qqq);
            for (int j: used) {
                ne[j] = e[j].w;
            }
            for (int j: upd) {
                if (j > i) break;
                ne[z[j].x] = z[j].w;
            }
            for (int j: used) {
                if (ne[j] >= w) dsu.Union(e[j].a, e[j].b);
            }
            ans[i] = dsu.query_size(s);
            dsu.re(undo, qqq);
        }
        for (int i: upd) {
            e[z[i].x].w = z[i].w;
        }
    }
    for (int i=0; i<q; ++i) {
        if (~ans[i]) cout << ans[i] << '\n';
    }
    return 0;
}
