#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define ll long long
#define eb emplace_back
#define iter(x) begin(x), end(x)
const int maxn = 100005;

int t[maxn];
 
signed main() {
	//ios_base::sync_with_stdio(false), cin.tie(0);
	int tt;
	scanf("%d", &tt);
	while (tt--) {
		int n, k, m;
		scanf("%d %d %d", &n, &k, &m);
		for (int i = 0; i < m; ++i) {
			int a, b, c;
			scanf("%d %d:%d", &a, &b, &c);
			t[i] = b * 60 + c;
		}
		sort(t, t + m);
		int cur = t[0];
		int ans = 0;
		for (int i = 1; i < m; ++i) {
			if (cur + k < t[i]) {
				++ans;
				cur = t[i];
			} else {
				cur = t[i];
			}
		}
		printf("%d\n", ans + 1);
	}		
	return 0;
}