#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
using pii = pair<int, int>;
#define F first
#define S second

vector<pii> g[501];
vector<int> ans;
bool vis[1025]{};
void dfs(int u){
    for(auto [v, id]: g[u]){
        if(!vis[id]){
            vis[id] = 1;
            dfs(v);
        }
    }
    ans.emplace_back(u);
}
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int m;
    cin >> m;
    for(int i=0 ; i<m ; ++i){
        int a, b;
        cin >> a >> b;
        g[a].eb(b, i);
        g[b].eb(a, i);
    }
    for(int i=1 ; i<501 ; ++i){
        sort(iter(g[i]), [&](pii a, pii b){
            return a.F < b.F;
        });
    }
    int root = 1;
    for(int i=1 ; i<501 ; ++i){
        if(g[i].size() & 1){
            root = i;
            break;
        }
    }
    dfs(root);
    reverse(iter(ans));
    for(auto i: ans) cout << i << '\n';
    return 0;
}
