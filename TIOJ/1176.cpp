#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int &h: heights) {
        cin >> h;
    }
    vector<int> ans(n, 0);
    vector<pair<int, int>> stk(n);
    for (int i = 0; i < heights.size(); ++i) {
        int h = heights[i];
        while (stk.size() && h >= stk.back().first) {
            auto [h0, i0] = stk.back();
            stk.pop_back();
            ans[i0] = i - i0;
        }
        stk.emplace_back(h, i);
    }
    while (stk.size()) {
        auto [h, i] = stk.back();
        stk.pop_back();
        ans[i] = n - i - 1;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}