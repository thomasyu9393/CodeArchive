#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
#define pii pair<int, int>
#define F first
#define S second

template<class T>
bool chmax(T &a, T b){return a < b ? (a = b, 1) : 0;}
template<class T>
bool chmin(T &a, T b){return a > b ? (a = b, 1) : 0;}

const int maxn = 200005;

struct SegTree {
    int sum[maxn<<2]{};
    bool tag[maxn<<2]{};
    void init(int l, int r, int o, int a[]) {
        if (l == r) return sum[o] = a[l], void();
        int mid = (l + r) / 2;
        init(l, mid, o<<1, a);
        init(mid + 1, r, o<<1|1, a);
        sum[o] = sum[o<<1] + sum[o<<1|1];
    }
    void push(int o) {
        if (tag[o]) {
            sum[o<<1] = 0;
            sum[o<<1|1] = 0;
            tag[o<<1] = 1;
            tag[o<<1|1] = 1;
        }
    }
    int query(int ql, int qr, int l, int r, int o) {
        if (ql > r || qr < l || ql > qr) return 0;
        if (ql <= l && r <= qr) {
            int res = sum[o];
            sum[o] = 0;
            tag[o] = 1;
            return res;
        }
        push(o);
        int mid = (l + r) / 2;
        int res = query(ql, qr, l, mid, o<<1) + query(ql, qr, mid + 1, r, o<<1|1);
        sum[o] = sum[o<<1] + sum[o<<1|1];
        return res;
    }
} sgt;


vector<pair<int, int>> g[maxn];

int val[maxn];
int pa[maxn], sz[maxn], nxt[maxn], dep[maxn];
int id[maxn], rt[maxn], tn = 0;
int dfs1(int u, int lst, int d) {
    pa[u] = lst;
    sz[u] = 1;
    nxt[u] = -1;
    dep[u] = d;
    for (auto v: g[u]) {
        int vv = v.F;
        if (vv != lst) {
            sz[u] += dfs1(vv, u, d + 1);
            if (nxt[u] == -1 || sz[vv] > sz[nxt[u]]) nxt[u] = vv;
        }
    }
    return sz[u];
}
void dfs2(int u, int lst, int w, int root) {
    id[u] = ++tn;
    val[id[u]] = w;
    rt[u] = root;
    for (auto v: g[u]) {
        int vv = v.F, ww = v.S;
        if (vv == nxt[u]) {
            dfs2(vv, u, ww, root);
            break;
        }
    }
    for (auto v: g[u]) {
        int vv = v.F, ww = v.S;
        if (vv != lst && vv != nxt[u]) {
            dfs2(vv, u, ww, vv);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i=1; i<n; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].eb(b, w);
        g[b].eb(a, w);
    }
    dfs1(1, 1, 0);
    dfs2(1, 1, 0, 1);
    sgt.init(1, n, 1, val);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        while (rt[a] != rt[b]) {
            if (dep[rt[a]] > dep[rt[b]]) swap(a, b); //dep[a] < dep[b]
            ans += sgt.query(id[rt[b]], id[b], 1, n, 1);
            b = pa[rt[b]];
        }
        if (a != b) {
            if (id[a] > id[b]) swap(a, b);
            ans += sgt.query(id[a] + 1, id[b], 1, n, 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
