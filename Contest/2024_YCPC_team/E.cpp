#include <bits/stdc++.h>
#define int long long 
using namespace std;

void sol() {
    int n, a, b, x;
    cin >> n >> a >> b >> x;
    if (n == 1) {
        cout << "Yes\n";
    } else if (x == 1) {
        if (a >= 1) cout <<"Yes\n";
        else cout <<"No\n";
    } else if (x == n) {
        if (b >= 1) cout <<"Yes\n";
        else cout <<"No\n";
    } else if (a >= 1 && b >= 1) {
        cout <<"Yes\n";
    } else {
        cout <<"No\n";
    }
}

signed main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) sol();
    return 0;
}