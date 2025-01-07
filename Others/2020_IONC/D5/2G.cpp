#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back

struct P {
    int c, h, i;
    P(int c, int h, int i): c(c), h(h), i(i) {}
    // color, height, index
};

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> arr[i][j];
            pref[i][j] = 1 + (arr[i][j] == arr[i - 1][j] ? pref[i - 1][j] : 0);
        }
    }
    int ans = 0;
    vector<P> stk;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cur = j;
            while (stk.size() && (pref[i][j] < stk.back().h || arr[i][j] != stk.back().c)) {
                ans = max(ans, stk.back().h * (j - stk.back().i));
                if (arr[i][j] == stk.back().c) cur = stk.back().i;
                stk.pop_back();
            }
            stk.emplace_back(P(arr[i][j], pref[i][j], cur));
        }
        while (stk.size()) {
            ans = max(ans, stk.back().h * (m - stk.back().i + 1));
            stk.pop_back();
        }
    }
    cout << ans << '\n';
    return 0;
}

/*
4 5
2 6 6 6 6
1 7 7 7 9
1 7 7 7 6
6 7 7 7 6

9

10 10
8 6 6 6 2 6 6 6 6 9
10 6 6 6 2 6 6 6 6 9
10 6 6 6 2 6 6 6 6 10
3 6 6 6 2 6 6 6 6 10
3 6 6 6 2 6 6 6 6 10
3 6 6 6 2 6 6 6 6 10
3 6 6 6 2 6 6 6 6 10
5 6 6 6 2 6 6 6 6 9
5 5 9 9 9 9 9 9 7 9
5 4 4 4 4 4 4 5 7 9

32

10 10
4 4 9 9 9 9 7 7 6 10
2 3 9 9 9 9 7 7 6 10
10 10 9 9 9 9 10 10 6 5
10 10 9 9 9 9 10 10 10 5
10 10 10 10 10 10 10 10 6 10
7 6 6 7 7 7 7 7 7 7
10 6 6 10 10 10 10 10 5 5
6 6 6 2 7 7 2 2 5 5
6 6 9 2 7 7 2 2 6 10
1 1 1 2 7 7 2 2 10 10

16
*/