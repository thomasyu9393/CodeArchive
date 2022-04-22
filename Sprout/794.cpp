#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rd(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}

int a[500001];
vector<int> v[500001];
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i=1 ; i<=n ; ++i){
        cin >> a[i];
        v[a[i]].eb(i);
    }
    while(q--){
        int l, r;
        cin >> l >> r;

        int best = 0, key;
        for(int i=0 ; i<30 ; ++i){
            int t = a[rd(l, r)];
            int cur = upper_bound(iter(v[t]), r) - lower_bound(iter(v[t]), l);
            if(cur > best){
                best = cur;
                key = t;
            }
        }

        int k = (r - l + 1) / 2;
        cout << (best > k ? key : 0) << '\n';
    }
}
