#include <iostream>
#include <stack>
#include <utility>
using namespace std;
#define ll long long
#define F first
#define S second

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        ll ans = 0;
        stack<pair<int, int>> stk;
        for(int i=0 ; i<n ; ++i){
            int x;
            cin >> x;
            while(stk.size() && x > stk.top().F){
                ans += stk.top().S;
                stk.pop();
            }
            if(stk.empty() || x < stk.top().F){
                if(stk.size()) ans++;
                stk.emplace(x, 1);
            }
            else{ // x == stk.top()
                ans += stk.top().S;
                if(stk.size() > 1) ans++;
                stk.top().S++;
            }
        }
        cout << ans << '\n';
    }
}
