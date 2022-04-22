#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)

const int N = 150005;
const ll oao = 1000000;

vector<int> v[N];
vector<ll> pf[N];
map<ll, ll> mp;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, k, q;
    cin >> n >> k >> q;
    for (int i=0; i<k; ++i) {
        int c, p;
        cin >> c >> p;
        v[p].eb(c);
    }
    for (int i=1; i<=n; ++i) {
        sort(iter(v[i]));
        pf[i].resize(v[i].size());
        for (int j=0; j<v[i].size(); ++j) {
            pf[i][j] = (j ? pf[i][j-1] : 0) + v[i][j];
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        ll c = 1ll * x * oao + y;
        if (mp[c]) {
            cout << mp[c] << '\n';
        } else {
            int b = (v[x].size() < v[y].size() ? y : x);
            int s = x + y - b;
            ll tmp = 0;
            for (int w: v[s]) {
                int pos = lower_bound(iter(v[b]), w) - begin(v[b]) - 1;
                if (pos < 0) tmp += 1ll * w * v[b].size();
                else tmp += pf[b][pos] + 1ll * w * (v[b].size() - pos - 1);
            }
            mp[c] = tmp;
            cout << tmp << '\n';
        }
    }
}
