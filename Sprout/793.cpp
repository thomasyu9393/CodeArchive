#include <bits/stdc++.h>
using namespace std;
#define ll long long

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rd(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}

unordered_map<int, ll> mp, cnt;
set<ll> st;
ll p[500001]{};
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, q;
    ll k;
    cin >> n >> k >> q;
    if(k == 1){
        while(q--) cout << '1';
        cout << '\n';
        return 0;
    }
    for(int i=1 ; i<=n ; ++i){
        int a;
        cin >> a;
        if(cnt[a]){
            ll t = mp[a];
            int s = ++cnt[a];
            if(s % k == 0){
                p[i] = p[i-1] - (k-1) * t;
            }
            else{
                p[i] = p[i-1] + t;
            }
        }
        else{
            ll t = rd(1e7, 1e12);
            while(st.find(t) != st.end()) t = rd(1e7, 1e12);
            mp[a] = t;
            cnt[a] = 1;
            st.insert(t);
            p[i] = p[i-1] + t;
        }
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << (p[r] - p[l-1] ? '0' : '1');
    } cout << '\n';
}
