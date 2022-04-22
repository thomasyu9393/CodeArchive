#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long

int ar[300005], ind[300005];
ll pref[300005]{};
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for (int i=1; i<=n; ++i) {
		cin >> ar[i];
		pref[i] = ar[i] + pref[i-1];
		ind[i-1] = i;
	}
	sort(ind, ind + n, [](int a, int b){
		return ar[a] < ar[b];
	});
	int l = 1, r = n;
	int cur = 0;
	while (l < r) {
		while (ind[cur] < l || ind[cur] > r) cur++;
		ll sum1 = pref[ind[cur]-1] - pref[l-1];
		ll sum2 = pref[r] - pref[ind[cur]];
		if (sum1 > sum2)
			r = ind[cur] - 1;
		else
			l = ind[cur] + 1;
	}
	cout << ar[l] << '\n';
	return 0;
}
