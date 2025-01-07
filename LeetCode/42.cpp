#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> stk; // index
        int ans = 0;
        for (int i = 0; i < height.size(); ++i) {
            int h = height[i];
            int top = 0;
            while (stk.size() && h >= height[stk.back()]) {
                ans += (min(h, height[stk.back()]) - top) * (i - stk.back() - 1);
                top = max(top, height[stk.back()]);
                stk.pop_back();
            }
            if (stk.size()) {
                ans += (min(h, height[stk.back()]) - top) * (i - stk.back() - 1);
            }
            stk.emplace_back(i);
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n;
    cin >> n;
    vector<int> height(n);
    for (int &h: height) {
        cin >> h;
    }
    Solution solution;
    cout << solution.trap(height) << '\n';
    return 0;
}