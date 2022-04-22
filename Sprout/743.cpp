#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <bitset>
using namespace std;

int cnt[450]{};

vector<int> v;
bitset<200005> dp;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n, k;
    cin >> n >> k;
    int s = sqrt(k);
    while (n--) {
        int x;
        cin >> x;
        if (x > s) {
            v.emplace_back(x);
        } else {
            cnt[x]++;
        }
    }
    for (int i=1; i<450; ++i) {
        for (int j=1; j<=cnt[i]; cnt[i]-=j, j<<=1) {
            v.emplace_back(i * j);
        }
        v.emplace_back(i * cnt[i]);
    }
    dp[0] = 1;
    for (int i: v) {
        dp |= dp << i;
    }
    for (int i=1; i<=k; ++i) {
        cout << dp[i];
    } cout << '\n';
}
