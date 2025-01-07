#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
using pii = pair<int, int>;

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin >> n;
    vector<pii> stk;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int h, tmp = i;
        cin >> h;
        while (stk.size() && h <= stk.back().first) {
            auto [h0, i0] = stk.back();
            stk.pop_back();
            ans = max(ans, h0 * (i - i0));
            tmp = i0;
        }
        stk.eb(h, tmp);
    }
    while (stk.size()) {
        auto [h, i] = stk.back();
        stk.pop_back();
        ans = max(ans, h * (n - i));
    }
    cout << ans << '\n';
    return 0;
}