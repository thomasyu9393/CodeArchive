#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <tuple>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 1000005;

vector<pair<int, int>> g[maxn];
vector<tuple<int, int, int>> bridge;
int D[maxn]{}, L[maxn]{}, tn = 0;
void dfs(int u, int pa){
    D[u] = L[u] = ++tn;
    for(auto [v, id]: g[u]){
        if(v == pa) continue;
        if(!D[v]){
            dfs(v, u);
            if(D[u] < L[v]) bridge.eb(u, v, id); 
            L[u] = min(L[u], L[v]);
        }
        L[u] = min(L[u], D[v]);
    }
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i=0 ; i<m ; ++i){
        int a, b;
        cin >> a >> b;
        g[a].eb(b, i);
        g[b].eb(a, i);
    }
    dfs(1, 1);
    sort(iter(bridge), [&](auto i, auto j){
        return get<2>(i) < get<2>(j);
    });
    for(auto [a, b, x]: bridge){
        cout << min(a, b) << ' ' << max(a, b) << '\n';
    }
    return 0;
}
