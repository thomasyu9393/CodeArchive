#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <set>
using namespace std;
const int maxn = 200005;

int s[maxn], t[maxn];
int ind[maxn];

multiset<int> st;

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, k;
	cin >> k >> n;
	for (int i=0; i<k; ++i) {
		cin >> s[i] >> t[i];
		ind[i] = i;
	}
	sort(ind, ind + k, [](int a, int b) {
		return t[a] < t[b];
	});
	int ans = 0;
	st.insert(0);
	for (int i=0; i<k; ++i) {
		int j = ind[i];
		auto it = st.lower_bound(s[j]);
		if (it == st.begin()) {
			if (st.size() < n) {
				st.insert(t[j]);
				++ans;
			}
		} else {
			st.erase(prev(it));
			st.insert(t[j]);
			++ans;
		}
	}
	cout << ans << '\n';
	return 0;
}