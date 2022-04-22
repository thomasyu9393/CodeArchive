#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 1000005;

vector<int> g[maxn], ap;
int D[maxn]{}, L[maxn]{}, tn = 0;
void dfs(int u, int pa){
    D[u] = L[u] = ++tn;
    int cnt = 0, isap = 0;
    for(int v: g[u]){
        if(v == pa) continue;
        if(!D[v]){
            dfs(v, u);
            cnt++;
            if(D[u] <= L[v]) isap = 1;
            L[u] = min(L[u], L[v]);
        }
        L[u] = min(L[u], D[v]);
    }
    if(u == pa && cnt < 2) isap = 0;
    if(isap) ap.eb(u);
}

signed main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
        g[a].eb(b);
        g[b].eb(a);
    }
    dfs(1, 1);
    sort(iter(ap));
    for(int i: ap){
        cout << i << '\n';
    }
    return 0;
}
