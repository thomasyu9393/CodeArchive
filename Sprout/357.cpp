#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 100005;

ll c[maxn], p[maxn];
int ind[maxn];
int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    ll n, m, r;
    cin >> n >> m >> r;
    ll cc = 0;
    for(int i=0 ; i<n ; ++i){
        cin >> p[i] >> c[i];
        ind[i] = i;
        if(p[i] == 100) cc += c[i];
    }
    if(cc <= r){
        cout << "-1\n";
        return 0;
    }
    sort(ind, ind + n, [](int i, int j){
        return p[i] > p[j];
    });
    priority_queue<ll> pq;
    ll time = 0, atk = 0, lef = m;
    int cur = 0;
    while(cur < n && lef > 0){
        while(cur < n && lef * 100 <= m * p[ind[cur]]){
            pq.push(c[ind[cur++]]);
        }
        time++;
        if(pq.size()){
            atk += pq.top();
            pq.pop();
        }
        lef = min(lef, lef - atk + r);
    }
    while(lef > 0){
        if(pq.size()){
            atk += pq.top();
            pq.pop();
        }
        time++;
        lef = min(lef, lef - atk + r);
    }
    cout << time << '\n';
}
