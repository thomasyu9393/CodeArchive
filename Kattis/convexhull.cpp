#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
using pii = pair<int, int>;
#define x first
#define y second
#define eb emplace_back
#define iter(x) begin(x), end(x)

pii operator-(pii a, pii b) {
	return {a.x - b.x, a.y - b.y};
}

int cross(pii a, pii b) {
	return a.x * b.y - a.y * b.x;
}

signed main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n;
	while (cin >> n) {
		if (n == 0) break;
		vector<pii> tmp(n);
		for (int i=0; i<n; ++i) {
			cin >> tmp[i].x >> tmp[i].y;
		}
		sort(iter(tmp));
		vector<pii> p, conv;
		pii lst = {10001, 10001};
		for (pii i: tmp) {
			if (i == lst) continue;
			p.eb(i);
			lst = i;
		}
		n = p.size();
		if (n <= 2) {
			cout << p.size() << '\n';
			for (pii i: p) {
				cout << i.x << ' ' << i.y << '\n';
			}
			continue;
		}
		for (int _=0; _<2; ++_) {
			int t = conv.size();
			for (pii i: p) {
				while (conv.size() - t >= 2 && cross(i - conv[conv.size() - 2], conv.back() - conv[conv.size() - 2]) >= 0) {
					conv.pop_back();
				}
				conv.eb(i);
			}
			conv.pop_back();
			reverse(iter(p));
		}
		cout << conv.size() << '\n';
		for (pii i: conv) {
			cout << i.x << ' ' << i.y << '\n';
		}
	}
	return 0;
}