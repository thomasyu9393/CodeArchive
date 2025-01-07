#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define iter(x) begin(x), end(x)
using pii = pair<int, int>;
const int maxn = 1000005;
const int maxm = 1005;

int mp[maxn]{};
int cnt[maxm]{};
queue<int> qu[maxm];

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t, _ = 0;
    while (cin >> t) {
        if (t == 0) break;
        for (int i = 1; i <= t; ++i) {
            int n;
            cin >> n;
            while (n--) {
                int x;
                cin >> x;
                mp[x] = i;
            }
            cnt[i] = 0;
            while (qu[i].size()) {
                qu[i].pop();
            }
        }
        string op;
        queue<int> team;
        cout << "Scenario #" << ++_ << '\n';
        while (cin >> op) {
            if (op[0] == 'S') {
                cout << '\n';
                break;
            } else if (op[0] == 'E') {
                int x, y;
                cin >> x;
                y = mp[x];
                qu[y].emplace(x);
                ++cnt[y];
                if (cnt[y] == 1) {
                    team.emplace(y);
                }
            } else if (op[0] == 'D') {
                int y = team.front();
                --cnt[y];
                if (cnt[y] == 0) {
                    team.pop();
                }
                cout << qu[y].front() << '\n';
                qu[y].pop();
            }
        }
    }
    return 0;
}