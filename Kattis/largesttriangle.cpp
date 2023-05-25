#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <iomanip>
using namespace std;
#define ll long long
using pll = pair<ll, ll>;
#define x first
#define y second
#define eb emplace_back
#define iter(x) begin(x), end(x)

pll operator-(pll a, pll b) {
	return {a.x - b.x, a.y - b.y};
}

ll cross(pll a, pll b) {
	return a.x * b.y - a.y * b.x;
}

vector<pll> p, conv;

ll calc(int a, int b, int c) {
	int n = conv.size();
	a %= n, b %= n, c %= n;
	ll res = cross(conv[b] - conv[a], conv[c] - conv[a]);
	return (res < 0 ? -res : res);
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	vector<pll> tmp(n);
	for (int i=0; i<n; ++i) {
		cin >> tmp[i].x >> tmp[i].y;
	}
	sort(iter(tmp));
	pll lst = {-1, -1};
	for (pll i: tmp) {
		if (i == lst) continue;
		p.eb(i);
		lst = i;
	}
	n = p.size();
	for (int _=0; _<2; ++_) {
		int t = conv.size();
		for (pll i: p) {
			while (conv.size() - t >= 2 && cross(i - conv[conv.size() - 2], conv.back() - conv[conv.size() - 2]) >= 0) {
				conv.pop_back();
			}
			conv.eb(i);
		}
		conv.pop_back();
		reverse(iter(p));
	}
	n = conv.size();
	if (n <= 2) {
		cout << 0 << '\n';
		return 0;
	}
	ll ans = 0;
	for (int i=0; i<n; ++i) {
		int k = i + 2;
		for (int l=1; l<n; ++l) {
			int j = i + l;
			while (calc(i, j, k) < calc(i, j, k + 1)) {
				++k;
			}
			ans = max(ans, calc(i, j, k));
		}
	}
	cout << fixed << setprecision(8) << 1.0 * ans / 2 << '\n';
	return 0;
}