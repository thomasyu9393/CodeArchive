#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define F first
#define S second
#define maxn 100005

int M[maxn];
map<int, int> mp;
void solve(){
    int n, m;
    cin >> n >> m;
    for(int i=0 ; i<n ; ++i){
        cin >> M[i];
    }
    mp.clear();
    while(m--){
        int x;
        cin >> x;
        mp[x]++;
    }
    queue<pii> qu;
    for(auto it = mp.rbegin() ; it != mp.rend() ; ++it){
        auto [ff, ss] = *it;
        for(int i=0 ; i<n && ss>0 ; ++i){
            if(M[i] >= ff){
                int omg = min(M[i] / ff, ss);
                M[i] -= omg * ff;
                ss -= omg;
                for(int j=0 ; j<omg ; ++j)
                    qu.push({ff, i});
            }
        }
        while(ss > 0 && qu.size() && ff < qu.front().F){
            auto [v, p] = qu.front();
            qu.pop();
            int omg = min(v / ff, ss);
            M[p] = M[p] + v - omg * ff;
            ss -= omg;
            for(int j=0 ; j<omg ; ++j)
                qu.push({ff, p});
        }
    }
    cout << qu.size() << '\n';
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
