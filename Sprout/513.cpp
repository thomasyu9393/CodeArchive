#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define F first
#define S second

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin >> n;
    stack<pair<ll, int>> stk;
    ll ans = 0;
    for(int i=0 ; i<n ; ++i){
        ll h;
        cin >> h;
        if(stk.empty() || h >= (stk.top()).F){
            stk.emplace(h, i);
        }
        else{
            int tmp = i;
            while(stk.size() && h < (stk.top()).F){
                auto [k, j] = stk.top();
                ans = max(ans, k * (i - j));
                tmp = j;
                stk.pop();
            }
            stk.emplace(h, tmp);
        }
    }
    while(stk.size()){
        auto [h, i] = stk.top();
        stk.pop();
        ans = max(ans, h * (n - i));
    }
    cout << ans << '\n';
}
