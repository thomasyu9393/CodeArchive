#include <bits/stdc++.h>
using namespace std;
#define int long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 300005;

using pii = pair<int, int>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sort(iter(x));

    vector<pair<int, int>> seg(m);
    for (int i = 0; i < m; ++i) {
        cin >> seg[i].first >> seg[i].second;
    }
    
    sort(iter(seg), [&](pii a, pii b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    });

    int cur_lef = x[n - 1] + 10;
    int min_lef = x[n - 1] + 10;
    int ans = 0;
    int ind = 0;
    int bad = 0;
    for (int i = n - 1; i >= 0; --i) {
        while (ind < m && seg[ind].second >= x[i]) {
            min_lef = min(min_lef, seg[ind].first);
            ++ind;
        }
        if (cur_lef > x[i]) {
            ++ans;
            cur_lef = min(cur_lef, min_lef);
        }
        if (cur_lef > x[i]) {
            bad = 1;
            break;
        }
    }
    cout << (bad ? -1 : ans) << '\n';
}

/*
3
3 3
1 2 4
1 3
2 3
2 5
6 7
2 3 6 7 10 13
1 1
3 8
4 6
12 1000000000
2 4
1 5
10 10
7 4
3 8 2 6 1 8 9
7 7
8 9
1 2
3 5
*/

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}