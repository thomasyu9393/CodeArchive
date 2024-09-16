#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn = 1000005;

int a[maxn]{}, dp[maxn]{};
void sol() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    dp[1] = max(0ll, a[1]);
    for (int i = 2; i <= n; ++i) {
        dp[i] = max(dp[i - 2] + a[i], dp[i - 1]);
    }
    cout << dp[n] << '\n';
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int _ = 1;
    //cin >>_;
    while (_--) sol();
    return 0;
}