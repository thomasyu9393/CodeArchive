#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 30005;

template<typename T>
bool chmax(T &a, T b){return a < b ? (a = b, 1) : 0;}
template<typename T>
bool chmin(T &a, T b){return a > b ? (a = b, 1) : 0;}

vector<int> g[maxn];
int D[maxn], L[maxn], tn = 0;
bool vis[maxn]{};
int best = 0, key = maxn;
int dfs(int u, int pa, int rt){
    D[u] = L[u] = ++tn;
    vis[u] = 1;
    int cnt = 0, ok = 0;
    int tot = 0, sub = 0;
    for(int v: g[u]){
        if(v == pa) continue;
        if(!D[v]){
            int res = dfs(v, u, rt);
            tot += res;
            cnt++;
            if(D[u] <= L[v]){
                ok = 1;
                sub += res;
            }
            L[u] = min(L[u], L[v]);
        }
        L[u] = min(L[u], D[v]);
    }
    if(u == pa && cnt < 2) ok = 0;
    if(ok && u != rt){
        if(sub > best){
            best = sub;
            key = u;
        }
        else if(sub == best){
            chmin(key, u);
        }
    }
    return tot + 1;
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m, k;
    cin >> n >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
        g[a].eb(b);
        g[b].eb(a);
    }
    cin >> k;
    dfs(k, k, k);
    if(!best){
        cout << "0\n";
    }
    else{
        int cnt = 0;
        for(int i=1 ; i<=n ; ++i){
            cnt += vis[i];
        }
        cout << key << ' ' << cnt - best << '\n';
    }
}
