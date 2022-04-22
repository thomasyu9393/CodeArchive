#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int v[50001];
bool check(int x) {
	int next, cnt = 0;
	for (int i=0 ; i<n ;) {
		next = v[i] + x;
		cnt++;
		if (cnt > k) return false;
		if (v[n-1] <= next && cnt <= k) return true;
		while (v[i] <= next) i++;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int L, R, M;
	cin >> n >> k;
	for (int i=0 ; i<n ; ++i) cin >> v[i];
	sort(v, v + n);
	if (k == 1) {
		cout << v[n-1] - v[0] << '\n';
	} else {
		L = 1;
		R = (v[n-1]-v[0]) / k + 1;
		while (L <= R) {
			M = L + ((R-L)>>1);
			if(check(M))
				R = M;
			else
				L = M + 1;
			if (L == R) break;
		}
		cout << R << '\n';
	}
	return 0;
}
