#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
const int maxn = 300005;

int ar[maxn];
ll pref[maxn]{};

int sp[maxn][19]{};
int query(int l, int r) {
	int p = __lg(r - l + 1);
	int x = sp[l][p], y = sp[r-(1<<p)+1][p];
	return ar[x] < ar[y] ? x : y;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	ar[0] = 1000000007;
	for (int i=1; i<=n; ++i) {
		cin >> ar[i];
		pref[i] = pref[i-1] + ar[i];
		sp[i][0] = i;
	}
	for (int j=0; j<__lg(n); ++j) {
		for (int i=1; i+(1<<j)<=n; ++i) {
			int x = sp[i][j], y = sp[i+(1<<j)][j];
			sp[i][j+1] = ar[x] < ar[y] ? x : y;
		}
	}
	int l = 1, r = n;
	while (l < r) {
		int mid = query(l, r);
		ll sum1 = pref[mid-1] - pref[l-1];
		ll sum2 = pref[r] - pref[mid];
		if (sum1 > sum2)
			r = mid - 1;
		else
			l = mid + 1;
	}
	cout << ar[l] << '\n';
	return 0;
}
