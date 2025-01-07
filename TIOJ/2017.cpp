#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin >> n;
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
        pref[i] += pref[i - 1];
    }
    vector<int> stk;
    int ans = 0;
    for (int i = n; i >= 0; --i) {
        while (stk.size() && pref[i] <= pref[stk.back()]) {
            stk.pop_back();
        }
        if (stk.size()) {
            ans += n - stk.back() + 1;
        }
        stk.emplace_back(i);
    }
    cout << ans << '\n';
    return 0;
}