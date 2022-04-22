#include <iostream>
#include <vector>
using namespace std;

int f(int n, int k) {
	if (n == 1) return 0;
	return (f(n-1, k) + k) % n;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	if(n == k + 1) {
		cout << f(n, m) + 1 << '\n';
	} else {
		vector<int> q;
		for(int i=1; i<=n; ++i) q.push_back(i);
		int t = 0;
		while(k--) {
			t = (t + m - 1) % q.size();
			q.erase(q.begin() + t);
		}
		t %= q.size();
		cout << q[t] << '\n';
	}
	return 0;
}
