#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
using namespace std;

#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)

const int maxn = 500005;

vector<tuple<int, int, int>> g[maxn];
vector<pair<int, int>> scc[maxn];
int w[maxn];

int D[maxn], L[maxn], tn = 0;
vector<int> stk;
bool instk[maxn]{};
int sccn = 0, no[maxn];
ll val[maxn]{};

void dfs(int u, int lst){
    D[u] = L[u] = ++tn;
    stk.eb(u);
    instk[u] = 1;
    for(auto [v, k, ind]: g[u]){
        if(ind == lst) continue;
        if(!D[v]){
            dfs(v, ind);
            L[u] = min(L[u], L[v]);
        }
        else if(instk[v]){
            L[u] = min(L[u], D[v]);
        }
    }
    if(L[u] == D[u]){
        int x;
        sccn++;
        do{
            x = stk.back();
            stk.pop_back();
            instk[x] = 0;
            no[x] = sccn;
            val[sccn] += w[x];
        } while(x != u);
    }
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i=1 ; i<=n ; ++i){
        cin >> w[i];
    }
    for(int i=0 ; i<m ; ++i){
        int u, v, x;
        cin >> u >> v >> x;
        g[u].eb(v, x, i);
    }
    for(int i=1 ; i<=n ; ++i){
        if(!D[i]) dfs(i, -1);
    }
    int indeg[maxn]{};
    for(int i=1 ; i<=n ; ++i){
        for(auto [j, k, l]: g[i]){
            if(no[i] != no[j]){
                scc[no[i]].eb(no[j], k);
                indeg[no[j]]++;
            }
            else{
                val[no[i]] += k;
            }
        }
    }
    ll dp[maxn]{};
    queue<int> qu;
    for(int i=1 ; i<=sccn ; ++i){
        if(!indeg[i]) qu.emplace(i);
    }
    while(qu.size()){
        int u = qu.front();
        qu.pop();
        dp[u] += val[u];
        for(auto [v, k]: scc[u]){
            dp[v] = max(dp[v], dp[u] + k);
            indeg[v]--;
            if(!indeg[v]) qu.emplace(v);
        }
    }
    cout << *max_element(dp + 1, dp + sccn + 1) << '\n';
}
